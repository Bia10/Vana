/*
Copyright (C) 2008-2016 Vana Development Team

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
#include "levels_packet.hpp"
#include "common/session.hpp"
#include "channel_server/maps.hpp"
#include "channel_server/player.hpp"
#include "channel_server/smsg_header.hpp"

namespace vana {
namespace channel_server {
namespace packets {

PACKET_IMPL(show_exp, game_experience exp, bool white, bool in_chat) {
	packet_builder builder;
	builder
		.add<packet_header>(SMSG_NOTICE)
		.add<int8_t>(3)
		.add<bool>(white)
		.add<game_experience>(exp)
		.add<bool>(in_chat)
		.add<int32_t>(0) // Wedding EXP
		.unk<int8_t>() // Hunting hours bonus exp rate
		.unk<int8_t>() // Some other rate that affects the final 
		.unk<int32_t>(); // Bonus wedding EXP (Married + in same party)

	if (in_chat) {
		int8_t spiritWeekBonusEXPRate = 0; // 0-100%
		builder.add<int8_t>(spiritWeekBonusEXPRate); // Spirit week bonus percentage
		if (spiritWeekBonusEXPRate > 0) {
			builder.add<int8_t>(0); // Additional bonus EXP for the next N quests
		}
	}

	builder
		.unk<int8_t>() // Party bonus EXP event rate
		.unk<int32_t>(); // Equip item bonus EXP
	return builder;
}

SPLIT_PACKET_IMPL(level_up, game_player_id player_id) {
	split_packet_builder builder;
	builder.player
		.add<packet_header>(SMSG_SKILL_SHOW)
		.add<game_player_id>(player_id)
		.add<int8_t>(0);

	builder.map.add_buffer(builder.player);
	return builder;
}

PACKET_IMPL(stat_ok) {
	packet_builder builder;
	builder.add<packet_header>(SMSG_EXCL_REQUEST);
	return builder;
}

SPLIT_PACKET_IMPL(job_change, game_player_id player_id) {
	split_packet_builder builder;
	builder.player
		.add<packet_header>(SMSG_SKILL_SHOW)
		.add<game_player_id>(player_id)
		.add<int8_t>(8);

	builder.map.add_buffer(builder.player);
	return builder;
}

}
}
}