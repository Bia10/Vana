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
#include "player_packet.hpp"
#include "common/client_ip.hpp"
#include "common/constant/stat.hpp"
#include "common/file_time.hpp"
#include "common/inter_header.hpp"
#include "common/session.hpp"
#include "common/wide_point.hpp"
#include "common/util/time.hpp"
#include "channel_server/channel_server.hpp"
#include "channel_server/key_maps.hpp"
#include "channel_server/map.hpp"
#include "channel_server/pet.hpp"
#include "channel_server/player.hpp"
#include "channel_server/player_data_provider.hpp"
#include "channel_server/player_packet_helper.hpp"
#include "channel_server/skill_macros.hpp"
#include "channel_server/skills.hpp"
#include "channel_server/smsg_header.hpp"
#include <unordered_map>

namespace vana {
namespace channel_server {
namespace packets {
namespace player {

PACKET_IMPL(connect_data, ref_ptr<vana::channel_server::player> player) {
	packet_builder builder;
	builder
		.add<packet_header>(SMSG_CHANGE_MAP)
		.add<int32_t>(channel_server::get_instance().get_channel_id())
		.add<uint8_t>(player->get_portal_count(true))
		.add<bool>(true) // Is a connect packet
		.add<int16_t>(0); // Some amount for a funny message at the top of the screen

	if (false) {
		size_t line_amount = 0;
		builder.add<string>("Message title");
		for (size_t i = 0; i < line_amount; i++) {
			builder.add<string>("Line");
		}
	}

	player->initialize_rng(builder);

	builder
		.add<int64_t>(-1) // Refers to packet sections that are included in here - all of them
		.add<game_player_id>(player->get_id())
		.add<string>(player->get_name(), 13)
		.add<game_gender_id>(player->get_gender())
		.add<game_skin_id>(player->get_skin())
		.add<game_face_id>(player->get_face())
		.add<game_hair_id>(player->get_hair());

	player->get_pets()->connect_packet(builder);
	player->get_stats()->connect_packet(builder);

	builder
		.add<int32_t>(0) // Gachapon EXP
		.add<game_map_id>(player->get_map_id())
		.add<game_portal_id>(player->get_map_pos())
		.unk<int32_t>() // Added in .62
		.add<uint8_t>(player->get_buddy_list_size());

	player->get_skills()->connect_packet_for_blessing(builder);
	player->get_inventory()->connect_packet(builder);
	player->get_skills()->connect_packet(builder);
	player->get_quests()->connect_packet(builder);

	// Must do significant testing on all of the following to verify
	builder
		.add<int16_t>(0) // I think this is the minigame record
		// foreach { int game, int win, int draw, int lose, int score }
		.add<int16_t>(0) // I think this is the couple ring record
		// foreach { int character_id, char[13] pair_name, long ring_cash_id, long other_ring_cash_id }
		.add<int16_t>(0) // I think this is the friendship ring record
		// foreach { int friend_id, char[13] friend_name, long ring_cash_id, long other_ring_cash_id, int friend_item_id }
		.add<int16_t>(0); // I think this is the marriage ring record
	// foreach { int marriage_id, int groom_id, int bride_id, ushort status, int groom_item_id, int bride_item_id, char[13] groom_name, char[13] bride_name}

	player->get_inventory()->rock_packet(builder); // Teleport Rock/VIP Rock maps
	player->get_monster_book()->connect_packet(builder);

	builder
		.add<int16_t>(0) // Newyear cards
		// foreach { int, int, string, byte, long, int, string, byte, byte, long, string }
		.add<int16_t>(0) // Amount of party quests (or extended quests? Maybe related to Battleship?)
		// foreach { game_quest_id quest_id, string quest_data }
		.add<int16_t>(0) // Not sure what this is, but it doesnt seem to be used in the client.
		// foreach { short, int }
		.add<file_time>(file_time{});
	return builder;
}

PACKET_IMPL(show_keys, key_maps *key_maps) {
	packet_builder builder;
	builder
		.add<packet_header>(SMSG_KEYMAP)
		.add<int8_t>(0);

	for (size_t i = 0; i < key_maps::key_count; i++) {
		if (key_maps::key_map *key_map = key_maps->get_key_map(i)) {
			builder
				.add<int8_t>(static_cast<int8_t>(key_map->type))
				.add<int32_t>(key_map->action);
		}
		else {
			builder
				.add<int8_t>(0)
				.add<int32_t>(0);
		}
	}
	return builder;
}

PACKET_IMPL(show_skill_macros, skill_macros *macros) {
	packet_builder builder;
	builder
		.add<packet_header>(SMSG_MACRO_LIST)
		.add<int8_t>(macros->get_max() + 1);

	for (int8_t i = 0; i <= macros->get_max(); i++) {
		if (skill_macros::skill_macro *macro = macros->get_skill_macro(i)) {
			builder
				.add<string>(macro->name)
				.add<bool>(macro->shout)
				.add<int32_t>(macro->skill1)
				.add<int32_t>(macro->skill2)
				.add<int32_t>(macro->skill3);
		}
		else {
			builder
				.add<string>("")
				.add<bool>(false)
				.add<int32_t>(0)
				.add<int32_t>(0)
				.add<int32_t>(0);
		}
	}
	return builder;
}

auto encode_player_stats(const data::type::player_stats_update &stats, uint32_t update_bits) -> packet_builder {
	packet_builder builder;
	builder.add<uint32_t>(update_bits);
	
	if (update_bits & constant::stat::skin)
		builder.add<game_skin_id>(stats.skin);
	if (update_bits & constant::stat::face)
		builder.add<game_face_id>(stats.face);
	if (update_bits & constant::stat::hair)
		builder.add<game_hair_id>(stats.hair);
	if (update_bits & constant::stat::pet_1)
		builder.add<game_pet_id>(stats.pet_1);
	if (update_bits & constant::stat::pet_2)
		builder.add<game_pet_id>(stats.pet_2);
	if (update_bits & constant::stat::pet_3)
		builder.add<game_pet_id>(stats.pet_3);
	if (update_bits & constant::stat::level)
		builder.add<game_player_level>(stats.level);
	if (update_bits & constant::stat::job)
		builder.add<game_job_id>(stats.job);
	if (update_bits & constant::stat::str)
		builder.add<game_stat>(stats.str);
	if (update_bits & constant::stat::dex)
		builder.add<game_stat>(stats.dex);
	if (update_bits & constant::stat::intl)
		builder.add<game_stat>(stats.intl);
	if (update_bits & constant::stat::luk)
		builder.add<game_stat>(stats.luk);
	if (update_bits & constant::stat::hp)
		builder.add<game_health>(stats.hp);
	if (update_bits & constant::stat::max_hp)
		builder.add<game_health>(stats.max_hp);
	if (update_bits & constant::stat::mp)
		builder.add<game_health>(stats.mp);
	if (update_bits & constant::stat::max_mp)
		builder.add<game_health>(stats.max_mp);
	if (update_bits & constant::stat::ap)
		builder.add<game_stat>(stats.ap);
	if (update_bits & constant::stat::sp)
		builder.add<game_stat>(stats.sp);
	if (update_bits & constant::stat::exp)
		builder.add<game_experience>(stats.exp);
	if (update_bits & constant::stat::fame)
		builder.add<game_fame>(stats.fame);
	if (update_bits & constant::stat::mesos)
		builder.add<game_mesos>(stats.mesos);

	if (update_bits & constant::stat::unk_3)
		builder.unk<int32_t>();

	return builder;
}

PACKET_IMPL(update_stat, const data::type::player_stats_update &stats, uint32_t update_bits, bool item_response) {
	packet_builder builder;
	builder
		.add<packet_header>(SMSG_PLAYER_UPDATE)
		.add<bool>(item_response);

	builder.add_buffer(encode_player_stats(stats, update_bits));

	if (update_bits & constant::stat::pet_flags)
		builder.unk<int8_t>();

	return builder;
}

PACKET_IMPL(change_channel, const ip &ip, connection_port port) {
	packet_builder builder;
	builder
		.add<packet_header>(SMSG_CHANNEL_CHANGE)
		.add<bool>(true)
		.add<client_ip>(client_ip{ip})
		.add<connection_port>(port);
	return builder;
}

PACKET_IMPL(show_message, const game_chat &msg, int8_t type) {
	packet_builder builder;
	builder
		.add<packet_header>(SMSG_MESSAGE)
		.add<int8_t>(type)
		.add<game_chat>(msg);

	if (type == notice_types::blue) {
		builder.add<int32_t>(0);
	}
	return builder;
}

PACKET_IMPL(group_chat, const string &name, const game_chat &msg, int8_t type) {
	packet_builder builder;
	builder
		.add<packet_header>(SMSG_MESSAGE_GROUP)
		.add<int8_t>(type)
		.add<string>(name)
		.add<game_chat>(msg);
	return builder;
}

PACKET_IMPL(instruction_bubble, const game_chat &msg, game_coord width, int16_t time, bool is_static, int32_t x, int32_t y) {
	packet_builder builder;

	if (width == -1) {
		width = static_cast<game_coord>(msg.size()) * 10;
		if (width < 40) {
			width = 40; // Anything lower crashes client/doesn't look good
		}
	}

	builder
		.add<packet_header>(SMSG_BUBBLE)
		.add<game_chat>(msg)
		.add<game_coord>(width)
		.add<int16_t>(time)
		.add<bool>(!is_static);

	if (is_static) {
		builder
			.add<int32_t>(x)
			.add<int32_t>(y);
	}
	return builder;
}

PACKET_IMPL(show_hp_bar, game_player_id player_id, int32_t hp, int32_t max_hp) {
	packet_builder builder;
	builder
		.add<packet_header>(SMSG_PARTY_HP_DISPLAY)
		.add<game_player_id>(player_id)
		.add<int32_t>(hp)
		.add<int32_t>(max_hp);
	return builder;
}

PACKET_IMPL(send_blocked_message, int8_t type) {
	packet_builder builder;
	builder
		.add<packet_header>(SMSG_CHANNEL_BLOCKED)
		.add<int8_t>(type);
	return builder;
}

PACKET_IMPL(send_week_event_message, const game_chat &msg) {
	packet_builder builder;
	builder
		.add<packet_header>(SMSG_SET_WEEK_EVENT_MESSAGE)
		.add<bool>(true)
		.add<game_chat>(msg);
	return builder;
}

PACKET_IMPL(stalk_result, ref_ptr<vana::channel_server::player> player) {
	packet_builder builder;
	builder
		.add<packet_header>(SMSG_STALK_RESULT);

	size_t offset = builder.get_size();
	
	builder
		.add<int32_t>(0);

	int32_t players = 0;
	
	player->get_map()->run_function_players([&](ref_ptr<vana::channel_server::player> p) {
		builder
			.add<game_player_id>(p->get_id())
			.add<bool>(false)
			.add<string>(p->get_name())
			.add<wide_point>(wide_point { p->get_pos() });

		players++;
	});
	
	builder.set<int32_t>(players, offset);

	return builder;
}

PACKET_IMPL(stalk_add_or_update_player, ref_ptr<vana::channel_server::player> player) {
	auto pos = player->get_pos();

	packet_builder builder;
	builder
		.add<packet_header>(SMSG_STALK_RESULT)
		.add<int32_t>(1)

		.add<game_player_id>(player->get_id())
		.add<bool>(false)
		.add<string>(player->get_name())
		.add<wide_point>(wide_point { pos });
		
	return builder;
}

PACKET_IMPL(stalk_remove_player, vector<game_player_id> player_ids) {
	packet_builder builder;
	builder
		.add<packet_header>(SMSG_STALK_RESULT)
		.add<int32_t>(player_ids.size());

	for (auto id : player_ids) {
		builder
			.add<game_player_id>(id)
			.add<bool>(true);
	}
		
	return builder;
}

PACKET_IMPL(damage_by_map, int32_t damage) {
	packet_builder builder;
	builder
		.add<packet_header>(SMSG_NOTIFY_HP_DAMAGE_BY_FIELD)
		.add<int32_t>(damage);

	return builder;
}
}
}
}
}