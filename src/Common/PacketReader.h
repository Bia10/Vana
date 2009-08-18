/*
Copyright (C) 2008-2009 Vana Development Team

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
#ifndef PACKETREADER_H
#define PACKETREADER_H

#include "Types.h"
#include <boost/tr1/memory.hpp>
#include <string>

using std::string;

struct Pos;

class PacketReader {
public:
	PacketReader();
	PacketReader(unsigned char *buffer, size_t length);

	template<typename T>
	T get();
	void skipBytes(int32_t len);
	int16_t getHeader(); // Basically getShort that always read at start
	string getString();
	string getString(size_t len);
	unsigned char * getBuffer();
	Pos getPos();
	size_t getBufferLength();

	PacketReader & reset(int32_t len = 0);
private:
	unsigned char *m_buffer;
	size_t m_length;
	size_t m_pos;
};

template<typename T>
T PacketReader::get() {
	T val = (*(T *)(m_buffer + m_pos));
	m_pos += sizeof(T);
	return val;
}

#endif
