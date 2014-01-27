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
#pragma once

#include "Types.h"
#include <memory>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

class PacketCreator;
class Player;
namespace soci {
	class row;
	class session;
}

struct Buddy {
	uint8_t oppositeStatus = 0;
	int32_t channel = 0;
	int32_t charId = 0;
	string_t name;
	string_t groupName;
};

struct BuddyInvite {
	bool send = true;
	int32_t id = 0;
	string_t name;
};

class PlayerBuddyList {
	NONCOPYABLE(PlayerBuddyList);
	NO_DEFAULT_CONSTRUCTOR(PlayerBuddyList);
public:
	PlayerBuddyList(Player *player);

	auto addBuddy(const string_t &name, const string_t &group, bool invite = true) -> uint8_t;
	auto removeBuddy(int32_t charId) -> void;

	auto getBuddy(int32_t charId) -> ref_ptr_t<Buddy> { return m_buddies[charId]; }
	auto listSize() const -> uint8_t { return m_buddies.size(); }
	auto getBuddyIds() -> vector_t<int32_t>;
	auto addBuddyInvite(const BuddyInvite &invite) -> void { m_pendingBuddies.push_back(invite); }

	auto addBuddies(PacketCreator &packet) -> void;
	auto checkForPendingBuddy() -> void;
	auto removePendingBuddy(int32_t id, bool accepted) -> void;
private:
	auto addBuddy(soci::session &sql, const soci::row &row) -> void;
	auto load() -> void;

	bool m_sentRequest = false;
	Player *m_player = nullptr;
	queue_t<BuddyInvite> m_pendingBuddies;
	hash_map_t<int32_t, ref_ptr_t<Buddy>> m_buddies;
};