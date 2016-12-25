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

#include "common/i_packet.hpp"
#include "common/types.hpp"
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace vana {
	DEFAULT_EXCEPTION(packet_content_exception, std::runtime_error);

	#ifdef DEBUG
	DEFAULT_EXCEPTION(packet_debug_exception, std::runtime_error);
	#endif

	class packet_reader {
	public:
		packet_reader() = default;
		packet_reader(unsigned char *buffer, size_t length);

		template <typename TValue>
		auto get() -> TValue;
		template <typename TValue>
		auto unk() -> TValue;
		template <typename TValue>
		auto get(size_t size) -> TValue;
		template <typename TValue>
		auto peek() -> TValue;
		template <typename TValue>
		auto skip() -> packet_reader &;

		auto skip(int32_t len) -> packet_reader &;
		auto get_buffer() const -> unsigned char *;
		auto get_buffer_length() const -> size_t;
		auto get_consumed_length() const -> size_t;
		auto reset(int32_t len = 0) -> packet_reader &;
		auto to_string() const -> string;
	private:
		friend auto operator <<(::std::ostream &out, const packet_reader &reader) -> std::ostream &;
		auto get_size() const -> size_t { return m_length; }

		template <typename TValue>
		auto skip_impl(TValue *) -> void;
		template <>
		auto skip_impl<bool>(bool *) -> void;
		template <>
		auto skip_impl<string>(string *) -> void;
		template <typename TElement>
		auto skip_impl(vector<TElement> *) -> void;

		template <typename TValue>
		auto get_impl(TValue *) -> TValue;
		template <typename TValue>
		auto get_sized_impl(size_t size, TValue *) -> TValue;

		template <typename TValue>
		auto get_impl_default() -> TValue;
		template <>
		auto get_impl<bool>(bool *) -> bool;
		template <>
		auto get_impl<double>(double *) -> double;
		template <>
		auto get_impl<string>(string *) -> string;
		template <>
		auto get_impl<int8_t>(int8_t *) -> int8_t;
		template <>
		auto get_impl<int16_t>(int16_t *) -> int16_t;
		template <>
		auto get_impl<int32_t>(int32_t *) -> int32_t;
		template <>
		auto get_impl<int64_t>(int64_t *) -> int64_t;
		template <>
		auto get_impl<uint8_t>(uint8_t *) -> uint8_t;
		template <>
		auto get_impl<uint16_t>(uint16_t *) -> uint16_t;
		template <>
		auto get_impl<uint32_t>(uint32_t *) -> uint32_t;
		template <>
		auto get_impl<uint64_t>(uint64_t *) -> uint64_t;
		template <>
		auto get_impl<milliseconds>(milliseconds *) -> milliseconds;
		template <>
		auto get_impl<seconds>(seconds *) -> seconds;
		template <>
		auto get_impl<minutes>(minutes *) -> minutes;
		template <>
		auto get_impl<hours>(hours *) -> hours;
		template <typename TElement>
		auto get_impl(vector<TElement> *) -> vector<TElement>;

		template <>
		auto get_sized_impl<string>(size_t size, string *) -> string;
		template <typename TElement>
		auto get_sized_impl(size_t size, vector<TElement> *) -> vector<TElement>;

		unsigned char *m_buffer = nullptr;
		size_t m_length = 0;
		size_t m_pos = 0;
	};

}
