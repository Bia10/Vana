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
#include "kite_packet.hpp"
#include "channel_server/kite.hpp"
#include "channel_server/smsg_header.hpp"

namespace vana {
namespace channel_server {
namespace packets {

PACKET_IMPL(spawn_kite, kite *kite) {
	packet_builder builder;
	builder
		.add<packet_header>(SMSG_KITE_SPAWN)
		.add<game_map_object>(kite->get_id())
		.add<game_item_id>(kite->get_item_id())
		.add<string>(kite->get_message())
		.add<string>(kite->get_owner_name())
		.add<point>(kite->get_owner_position());
	return builder;
}

PACKET_IMPL(despawn_kite, kite *kite, kite_despawn_reason reason) {
	packet_builder builder;
	builder
		.add<packet_header>(SMSG_KITE_DESPAWN)
		.add<int8_t>((int8_t)reason)
		.add<game_map_object>(kite->get_id());
	return builder;
}

PACKET_IMPL(kite_spawn_blocked) {
	packet_builder builder;
	builder
		.add<packet_header>(SMSG_KITE_CREATE_FAILED);
	return builder;
}

}
}
}
