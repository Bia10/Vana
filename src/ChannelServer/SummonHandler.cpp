/*
Copyright (C) 2008-2014 Vana Development Team

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; version 2
of the License.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
#include "SummonHandler.h"
#include "GameLogicUtilities.h"
#include "LoopingId.h"
#include "Maps.h"
#include "MovementHandler.h"
#include "PacketReader.h"
#include "SkillConstants.h"
#include "Player.h"
#include "PlayerPacket.h"
#include "SkillDataProvider.h"
#include "Summon.h"
#include "SummonsPacket.h"

LoopingId<int32_t> SummonHandler::summonIds;

auto SummonHandler::loopId() -> int32_t {
	return summonIds.next();
}

auto SummonHandler::useSummon(Player *player, int32_t skillId, uint8_t level) -> void {
	Summon *summon = new Summon(loopId(), skillId, level);
	bool puppet = GameLogicUtilities::isPuppet(skillId);
	removeSummon(player, puppet, false, SummonMessages::None);
	Pos playerPosition = player->getPos();
	Pos summonPosition;
	if (puppet) {
		playerPosition.x += 200 * (player->isFacingRight() ? 1 : -1);
		player->getMap()->findFloor(playerPosition, summonPosition);
	}
	else {
		summonPosition = playerPosition;
	}
	summon->setPos(summonPosition);
	player->getSummons()->addSummon(summon, SkillDataProvider::getInstance().getSkill(skillId, level)->time);
	SummonsPacket::showSummon(player, summon, true);
}

auto SummonHandler::removeSummon(Player *player, bool puppet, bool packetOnly, int8_t showMessage, bool fromTimer) -> void {
	// Maybe we don't need the packetOnly thing...? We don't use it anyway...

	Summon *summon = puppet ? player->getSummons()->getPuppet() : player->getSummons()->getSummon();
	if (summon != nullptr) {
		SummonsPacket::removeSummon(player, summon, showMessage);
		if (!packetOnly) {
			player->getSummons()->removeSummon(puppet, fromTimer);
		}
	}
}

auto SummonHandler::showSummon(Player *player) -> void {
	if (Summon *summon = player->getSummons()->getSummon()) {
		summon->setPos(player->getPos());
		SummonsPacket::showSummon(player, summon, false);
	}
}

auto SummonHandler::showSummons(Player *fromPlayer, Player *toPlayer) -> void {
	if (Summon *summon = fromPlayer->getSummons()->getSummon()) {
		SummonsPacket::showSummon(fromPlayer, summon, false, toPlayer);
	}
	if (Summon *puppet = fromPlayer->getSummons()->getPuppet()) {
		SummonsPacket::showSummon(fromPlayer, puppet, false, toPlayer);
	}
}

auto SummonHandler::moveSummon(Player *player, PacketReader &packet) -> void {
	int32_t summonId = packet.get<int32_t>();

	// I am not certain what this is, but in the Odin source they seemed to think it was original position. However, it caused AIDS.
	packet.skipBytes(4);

	Summon *summon = player->getSummons()->getSummon(summonId);
	if (summon == nullptr || summon->getType() == Summon::Static) {
		// Up to no good, lag, or something else
		return;
	}

	const Pos &startPos = summon->getPos(); // Original gangsta
	MovementHandler::parseMovement(summon, packet);
	packet.reset(10);
	SummonsPacket::moveSummon(player, summon, startPos, packet.getBuffer(), (packet.getBufferLength() - 9));
}

auto SummonHandler::damageSummon(Player *player, PacketReader &packet) -> void {
	int32_t summonId = packet.get<int32_t>();
	int8_t unk = packet.get<int8_t>();
	int32_t damage = packet.get<int32_t>();
	int32_t mobId = packet.get<int32_t>();

	if (Summon *summon = player->getSummons()->getPuppet()) {
		summon->doDamage(damage);
		//SummonsPacket::damageSummon(player, summonId, unk, damage, mobId); // TODO: Find out if this packet even sends anymore
		if (summon->getHP() <= 0) {
			removeSummon(player, true, false, SummonMessages::None, true);
		}
	}
}