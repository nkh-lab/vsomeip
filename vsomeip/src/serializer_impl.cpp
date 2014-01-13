//
// serializer_impl.cpp
//
// Date: 	Nov 29, 2013
// Author: 	Lutz Bichler
//
// This file is part of the BMW Some/IP implementation.
//
// Copyright © 2013 Bayerische Motoren Werke AG (BMW). 
// All rights reserved.
//
#include <cstring>

#include <vsomeip/impl/byteorder_impl.hpp>
#include <vsomeip/impl/serializer_impl.hpp>

namespace vsomeip {

serializer_impl::serializer_impl()
	: data_(0), length_(0), position_(0), remaining_(0) {
}

serializer_impl::~serializer_impl() {
};

bool serializer_impl::serialize(serializable &_from) {
	return _from.serialize(this);
}

bool serializer_impl::serialize(const uint8_t _value) {
	if (1 > remaining_)
		return false;

	*position_++ = _value;
	remaining_--;

	return true;
}

bool serializer_impl::serialize(const uint16_t _value) {
	if (2 > remaining_)
		return false;

	*position_++ = VSOMEIP_WORD_BYTE1(_value);
	*position_++ = VSOMEIP_WORD_BYTE0(_value);
	remaining_ -= 2;

	return true;
}

bool serializer_impl::serialize(const uint32_t _value, bool _omit_last_byte) {
	if (3 > remaining_ || (!_omit_last_byte && 4 > remaining_))
		return false;

	if (!_omit_last_byte) {
		*position_++ = VSOMEIP_LONG_BYTE3(_value);
		remaining_--;
	}
	*position_++ = VSOMEIP_LONG_BYTE2(_value);
	*position_++ = VSOMEIP_LONG_BYTE1(_value);
	*position_++ = VSOMEIP_LONG_BYTE0(_value);
	remaining_ -= 3;

	return true;
}

bool serializer_impl::serialize(const uint8_t *_data, uint32_t _length) {
	if (_length > remaining_)
		return false;

	::memcpy(position_, _data, _length);
	position_ += _length;
	remaining_ -= _length;

	return true;
}

const uint8_t * serializer_impl::get_buffer() const {
	return data_;
}

uint32_t serializer_impl::get_length() const {
	return length_;
}

void serializer_impl::get_buffer_info(uint8_t *&_data, uint32_t &_length) const {
	_data = data_;
	_length = length_;
}

void serializer_impl::create_buffer(uint32_t _length) {
	if (0 != data_)
		delete [] data_;

	data_ = new uint8_t[_length];
	// TODO: check memory allocation

	length_ = _length;
	position_ = data_;
	remaining_ = length_;
}

void serializer_impl::set_buffer(uint8_t *_data, uint32_t _length) {
	if (0 != data_)
		delete [] data_;

	data_ = _data;
	length_ = _length;
	position_ = data_;
	remaining_ = length_;
}

} // namespace vsomeip





