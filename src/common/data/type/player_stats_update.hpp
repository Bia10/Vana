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

#include "common/types.hpp"

namespace vana {
	namespace data {
		namespace type {
			struct player_stats_update {
				game_skin_id skin;
				game_face_id face;
				game_hair_id hair;
				game_pet_id pet_1, pet_2, pet_3;
				game_player_level level;
				game_job_id job;
				game_stat str, dex, intl, luk;
				game_health hp, max_hp;
				game_health mp, max_mp;
				game_stat ap, sp;
				game_experience exp;
				game_fame fame;
				game_mesos mesos;
			};
		}
	}
}