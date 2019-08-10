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

#ifndef OndraRT__LINEDRIVER_H_
#define OndraRT__LINEDRIVER_H_

#include <cstdint>

namespace OndraRT {

namespace Typograph {

/**
 * @brief A driver allowing output into a line oriented device
 */
class LineDriver {
  public:
    enum FontStyle {
      FS_DEFAULT,
      FS_NORMAL,
      FS_ITALIC,
    };

    enum FontWeight {
      FW_DEFAULT,
      FW_NORMAL,
      FW_BOLD,
    };

    enum Color {
      C_DEFAULT,
      C_BLACK,
      C_RED,
      C_GREEN,
      C_YELLOW,
      C_BLUE,
      C_MAGENTA,
      C_CYAN,
      C_WHITE,
    };

  public:
    /**
     * @brief Ctor
     */
    LineDriver();

    /**
     * @brief Dtor
     */
    virtual ~LineDriver();

    /* -- avoid copying */
    LineDriver(
        const LineDriver&) = delete;
    LineDriver& operator =(
        const LineDriver&) = delete;

    /**
     * @brief Skip specified number of characters at current line
     *
     * @param chars_ The number of skipped characters
     */
    virtual void skipChars(
        int chars_) = 0;

    /**
     * @brief Write a text
     *
     * @param text_ The text
     * @param length_ Length of the text
     */
    virtual void writeText(
        const char* text_,
        int length_) = 0;

    /**
     * @brief Finish current line
     */
    virtual void breakLine() = 0;

    /**
     * @brief Set font style
     */
    virtual void setFontStyle(
        FontStyle style_) = 0;

    /**
     * @brief Set font weight
     */
    virtual void setFontWeight(
        FontWeight weight_) = 0;

    /**
     * @brief Set foreground color
     */
    virtual void setForegroundColor(
        Color color_) = 0;

    /**
     * @brief Set background color
     */
    virtual void setBackgroundColor(
        Color color_) = 0;
};

} /* -- namespace Typograph */

} /* -- namespace OndraRT */

#endif /* OndraRT__LINEDRIVER_H_ */
