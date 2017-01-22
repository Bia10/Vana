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
#include "fame_packet.hpp"
#include "common/session.hpp"
#include "channel_server/player.hpp"
#include "channel_server/player_data_provider.hpp"
#include "channel_server/smsg_header.hpp"

namespace vana {
namespace channel_server {
namespace packets {
namespace fame {

PACKET_IMPL(send_error, errors reason) {
	packet_builder builder;
	builder
		.add<packet_header>(SMSG_FAME)
		.add<int8_t>(static_cast<int8_t>(reason));
	return builder;
}

PACKET_IMPL(send_fame, const string &name, uint8_t type, int32_t new_fame) {
	packet_builder builder;
	builder
		.add<packet_header>(SMSG_FAME)
		.add<int8_t>(static_cast<int8_t>(errors::no_error_fame_sent))
		.add<string>(name)
		.add<int8_t>(type)
		.add<int32_t>(new_fame);
	return builder;
}

PACKET_IMPL(receive_fame, const string &name, uint8_t type) {
	packet_builder builder;
	builder
		.add<packet_header>(SMSG_FAME)
		.add<int8_t>(static_cast<int8_t>(errors::no_error_fame_received))
		.add<string>(name)
		.add<int8_t>(type);
	return builder;
}

}
}
}
}