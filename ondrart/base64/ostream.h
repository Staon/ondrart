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

#ifndef OndraRT__ONDRART_BASE64_OSTREAM_H_
#define OndraRT__ONDRART_BASE64_OSTREAM_H_

#include <cstdint>
#include <iostream>

namespace OndraRT {

namespace Base64 {

class OStreamBuffer final : public std::streambuf {
  private:
    std::ostream* sink;
    const int len_quat;
    int quaternions;

    enum { BUFFER_SIZE = 3 };
    char_type buffer[BUFFER_SIZE];

    void pushTriplet(
        const std::uint8_t* ibuff_,
        const std::uint8_t* current_);

    /* -- streambuf interface */
    virtual int_type overflow(
        int_type ch) override;

  public:
    explicit OStreamBuffer(
        std::ostream* sink_,
        int quaternions_);

    virtual ~OStreamBuffer();

    /* -- avoid copying */
    OStreamBuffer(
        const OStreamBuffer&) = delete;
    OStreamBuffer& operator =(
        const OStreamBuffer&) = delete;

    /**
     * @brief Finish current stream - flush last bytes and fill the padding
     */
    void finish();
};

/**
 * @brief Base64 output stream
 */
class OStream : public std::ostream {
  private:
    OStreamBuffer buffer;

  public:
    /**
     * @brief Ctor
     *
     * @param sink_ A decorated output stream. The ownership is not taken.
     * @param line_length_ Length of one base64 encoded line. If the value
     *     is negative, the output is not broken into lines. The value
     *     is rounded to the closest lesser multiplication of 4.
     */
    explicit OStream(
        std::ostream* sink_,
        int line_length_ = -1);

    /**
     * @brief Dtor
     */
    virtual ~OStream();

    /**
     * @brief Finish current stream - flush last bytes and fill the padding
     */
    void finish();
};

} /* -- namespace Base64 */

} /* -- namespace OndraRT */

#endif /* OndraRT__ONDRART_BASE64_OSTREAM_H_ */
