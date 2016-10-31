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
#pragma once

#include "common/point.hpp"
#include "common/types.hpp"

namespace vana {
	namespace channel_server {
		class kite {
			NO_DEFAULT_CONSTRUCTOR(kite);
			NONCOPYABLE(kite);
		public:
			kite(game_map_id map_id, game_item_id item_id, const point &owner_pos, game_player_id owner, const string& owner_name, const string& message) :
			m_owner{ owner },
			m_owner_name{ owner_name },
			m_map_id{ map_id },
			m_item_id{ item_id },
			m_owner_position{ owner_pos },
			m_message{ message } {
			}

			auto set_id(game_map_object id) -> void { m_id = id; }
			auto set_spawned_at_time(time_point time) -> void { m_spawned_at_time = time; }

			auto get_owner() const -> game_player_id { return m_owner; }
			auto get_owner_name() const -> const string& { return m_owner_name; }
			auto get_map_id() const -> game_map_id { return m_map_id; }
			auto get_id() const -> game_map_object { return m_id; }
			auto get_owner_position() const -> const point& { return m_owner_position; }
			auto get_item_id() const -> game_item_id { return m_item_id; }
			auto get_message() const -> const string& { return m_message; }
			auto get_spawned_at_time() const -> time_point { return m_spawned_at_time; }

		private:
			game_player_id m_owner = 0;
			game_map_id m_map_id = 0;
			game_map_object m_id = 0;
			game_item_id m_item_id;
			point m_owner_position;
			string m_owner_name;
			string m_message;
			time_point m_spawned_at_time;
		};
	}
}