/*
 * Copyright (C) 2019 Ondrej Starek
 *
 * This file is part of OndraRT.
 *
 * OndraRT is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version.
 *
 * OndraRT is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with OndraRT.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <assert.h>

#include <ondrart/base64/ostream.h>

namespace OndraRT {

namespace Base64 {

namespace {

constexpr char table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

template<typename Src_>
const std::uint8_t* toByteArray(
    const Src_* src_array_) {
  static_assert(sizeof(Src_) == 1, "invalid character type");
  return reinterpret_cast<const std::uint8_t*>(src_array_);
}

} /* -- namespace */

void OStreamBuffer::pushTriplet(
    const std::uint8_t* ibuff_,
    const std::uint8_t* current_) {
  if(ibuff_ < current_) {
    char obuff_[4];
    std::uint8_t c_((*ibuff_ & 0xfc) >> 2);
    obuff_[0] = table[c_];

    c_ = (*ibuff_ & 0x03) << 4;
    ++ibuff_;
    if(ibuff_ < current_)
      c_ |= (*ibuff_ & 0xf0) >> 4;
    obuff_[1] = table[c_];

    if(ibuff_ < current_) {
      c_ = (*ibuff_ & 0x0f) << 2;
      ++ibuff_;
      if(ibuff_ < current_)
        c_ |= (*ibuff_ & 0xc0) >> 6;
      obuff_[2] = table[c_];

      if(ibuff_ < current_)
        obuff_[3] = table[*ibuff_ & 0x3f];
      else
        obuff_[3] = '=';
    }
    else {
      obuff_[2] = '=';
      obuff_[3] = '=';
    }

    /* -- write the converted quaternion */
    sink->write(obuff_, 4);

    /* -- break the line if it's needed */
    if(len_quat > 0) {
      ++quaternions;
      if(quaternions >= len_quat) {
        quaternions = 0;
        *sink << '\n';
      }
    }
  }
}

OStreamBuffer::OStreamBuffer(
    std::ostream* sink_,
    int quaternions_) :
  sink(sink_),
  len_quat(quaternions_),
  quaternions(0) {
  assert(sink != nullptr);

  setp(buffer, buffer + BUFFER_SIZE);
}

OStreamBuffer::~OStreamBuffer() {
  /* -- write the remaining data with padding */
  pushTriplet(toByteArray(buffer), toByteArray(pptr()));
}

OStreamBuffer::int_type OStreamBuffer::overflow(
    OStreamBuffer::int_type ch) {
  /* -- write the triplet */
  pushTriplet(toByteArray(buffer), toByteArray(pptr()));

  /* -- start new one */
  char* begin_(buffer);
  if(ch != traits_type::eof()) {
    buffer[0] = traits_type::to_char_type(ch);
    ++begin_;
  }
  setp(begin_, buffer + BUFFER_SIZE);

  return traits_type::not_eof(ch);
}

void OStreamBuffer::finish() {
  /* -- write the remaining data with padding */
  pushTriplet(toByteArray(buffer), toByteArray(pptr()));

  /* -- prepare for next triplet */
  setp(buffer, buffer + BUFFER_SIZE);
}

OStream::OStream(
    std::ostream* os_,
    int line_length_) :
  std::ostream(&buffer),
  buffer(os_, (line_length_ <= 3)?-1:(line_length_ / 4)) {

}

OStream::~OStream() {

}

void OStream::finish() {
  buffer.finish();
}

} /* -- namespace Base64 */

} /* -- namespace OndraRT */
