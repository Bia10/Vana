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

#include "common/packet_builder.hpp"
#include "common/types.hpp"

namespace vana {
	namespace channel_server {
		class player;

		namespace packets {
			namespace fame {
				enum class errors : int8_t {
					no_error_fame_sent = 0,
					incorrect_user = 1,
					level_under15 = 2,
					already_famed_today = 3,
					famed_this_month = 4,
					no_error_fame_received = 5,
				};
				
				PACKET(send_error, errors reason);
				PACKET(send_fame, const string &name, uint8_t type, int32_t new_fame);
				PACKET(receive_fame, const string &name, uint8_t type);
			}
		}
	}
}