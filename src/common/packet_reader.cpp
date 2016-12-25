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
#include "packet_reader.hpp"
#include "common/util/string.hpp"
#include <iomanip>
#include <sstream>
#include <stdexcept>

namespace vana {

packet_reader::packet_reader(unsigned char *buffer, size_t length) :
	m_buffer{buffer},
	m_length{length}
{
}

auto packet_reader::skip(int32_t len) -> packet_reader & {
	m_pos += len;
	return *this;
}

auto packet_reader::get_buffer() const -> unsigned char * {
	return m_buffer + m_pos;
}

auto packet_reader::get_buffer_length() const -> size_t {
	return get_size() - m_pos;
}

auto packet_reader::get_consumed_length() const -> size_t {
	return m_pos;
}

auto packet_reader::reset(int32_t len) -> packet_reader & {
	if (len >= 0) {
		m_pos = len;
	}
	else {
		m_pos = get_size() + len; // In this case, len is negative here so we take the total length and plus (minus) it by len
	}

	return *this;
}

auto packet_reader::to_string() const -> string {
	return vana::util::str::bytes_to_hex(get_buffer(), get_buffer_length());
}


template <typename TValue>
auto packet_reader::get() -> TValue {
	auto v = get_impl(static_cast<TValue *>(nullptr));
	return v;
}

template <typename TValue>
auto packet_reader::unk() -> TValue {
	auto v = get_impl(static_cast<TValue *>(nullptr));
	return v;
}

template <typename TValue>
auto packet_reader::get(size_t size) -> TValue {
	auto v = get_sized_impl(size, static_cast<TValue *>(nullptr));
	return v;
}

template <typename TValue>
auto packet_reader::peek() -> TValue {
	size_t pos = get_consumed_length();
	auto val = get<TValue>();
	m_pos = pos;
	return val;
}

template <typename TValue>
auto packet_reader::skip() -> packet_reader & {
	skip_impl(static_cast<TValue *>(nullptr));
	return *this;
}

template <typename TValue>
auto packet_reader::skip_impl(TValue *) -> void {
	m_pos += sizeof(TValue);
}

template <>
auto packet_reader::skip_impl<bool>(bool *) -> void {
	m_pos += 1;
}

template <>
auto packet_reader::skip_impl<string>(string *) -> void {
	size_t length = get<uint16_t>();
	m_pos += length;
}

template <typename TElement>
auto packet_reader::skip_impl(vector<TElement> *) -> void {
	size_t length = get<uint32_t>();
	m_pos += length * sizeof(TElement);
}

template <typename TValue>
auto packet_reader::get_impl(TValue *) -> TValue {
	packet_serialize<TValue> x;
	return x.read(*this);
}

template <typename TValue>
auto packet_reader::get_sized_impl(size_t size, TValue *) -> TValue {
	static_assert(false, "T is not appropriately specialized for that type");
	throw std::logic_error{"T is not appropriately specialized for that type"};
}

template <typename TValue>
auto packet_reader::get_impl_default() -> TValue {
	if (sizeof(TValue) > get_buffer_length()) {
		throw packet_content_exception{"Packet data longer than buffer allows"};
	}
	TValue val = *reinterpret_cast<TValue *>(m_buffer + m_pos);
	m_pos += sizeof(TValue);
	return val;
}

template <>
auto packet_reader::get_impl<bool>(bool *) -> bool {
#ifdef DEBUG
	// Address programming errors in debug
	int8_t byte = get_impl_default<int8_t>();
	if (byte != 0 && byte != 1) throw packet_debug_exception{"Packet data inconsistent with bool type"};
	return byte != 0;
#else
	return get_impl_default<int8_t>() != 0;
#endif
}

template <>
auto packet_reader::get_impl<double>(double *) -> double {
	return get_impl_default<double>();
}

template <>
auto packet_reader::get_impl<int8_t>(int8_t *) -> int8_t {
	return get_impl_default<int8_t>();
}

template <>
auto packet_reader::get_impl<int16_t>(int16_t *) -> int16_t {
	return get_impl_default<int16_t>();
}

template <>
auto packet_reader::get_impl<int32_t>(int32_t *) -> int32_t {
	return get_impl_default<int32_t>();
}

template <>
auto packet_reader::get_impl<int64_t>(int64_t *) -> int64_t {
	return get_impl_default<int64_t>();
}

template <>
auto packet_reader::get_impl<uint8_t>(uint8_t *) -> uint8_t {
	return get_impl_default<uint8_t>();
}

template <>
auto packet_reader::get_impl<uint16_t>(uint16_t *) -> uint16_t {
	return get_impl_default<uint16_t>();
}

template <>
auto packet_reader::get_impl<uint32_t>(uint32_t *) -> uint32_t {
	return get_impl_default<uint32_t>();
}

template <>
auto packet_reader::get_impl<uint64_t>(uint64_t *) -> uint64_t {
	return get_impl_default<uint64_t>();
}

template <>
auto packet_reader::get_impl<milliseconds>(milliseconds *) -> milliseconds {
	return milliseconds{get_impl_default<int32_t>()};
}

template <>
auto packet_reader::get_impl<seconds>(seconds *) -> seconds {
	return seconds{get_impl_default<int32_t>()};
}

template <>
auto packet_reader::get_impl<minutes>(minutes *) -> minutes {
	return minutes{get_impl_default<int32_t>()};
}

template <>
auto packet_reader::get_impl<hours>(hours *) -> hours {
	return hours{get_impl_default<int32_t>()};
}

template <>
auto packet_reader::get_impl<string>(string *) -> string {
	size_t size = get_impl_default<uint16_t>();
	return get<string>(size);
}

template <typename TElement>
auto packet_reader::get_impl(vector<TElement> *) -> vector<TElement> {
	size_t size = get_impl_default<uint32_t>();
	return get<vector<TElement>>(size);
}

template <>
auto packet_reader::get_sized_impl<string>(size_t size, string *) -> string {
	if (size > get_buffer_length()) {
		throw packet_content_exception{"Packet string longer than buffer allows"};
	}
	string s{reinterpret_cast<char *>(m_buffer + m_pos), size};
	m_pos += size;
	return s;
}

template <typename TElement>
auto packet_reader::get_sized_impl(size_t size, vector<TElement> *) -> vector<TElement> {
	vector<TElement> vec;
	for (size_t i = 0; i < size; i++) {
		vec.push_back(get<TElement>());
	}
	return vec;
}

inline
auto operator <<(std::ostream &out, const packet_reader &reader) -> std::ostream & {
	out << reader.to_string();
	return out;
}

}
