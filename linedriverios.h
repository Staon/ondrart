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

#ifndef OndraRT__LINEDRIVERIOS_H_
#define OndraRT__LINEDRIVERIOS_H_

#include <iosfwd>

#include "linedriver.h"

namespace OndraRT {

namespace Typograph {

/**
 * @brief Simple line driver based on C++ output streams
 *
 * The driver allows output of text but it doesn't support any text attributes
 * and colors.
 */
class LineDriverIos : public LineDriver {
  public:
    enum LineSync {
      ASYNC,  /**< the output is not synced at the end of line */
      SYNC,   /**< the output is flushed at the end of every line */
    };

  public:
    /**
     * @brief Ctor
     *
     * @param os_ The output stream. The ownership is not taken.
     * @param sync_ Flushing of every line
     */
    explicit LineDriverIos(
        std::ostream* os_,
        LineSync sync_ = ASYNC);

    /**
     * @brief Dtor
     */
    virtual ~LineDriverIos();

    /* -- avoid copying */
    LineDriverIos(
        const LineDriverIos&) = delete;
    LineDriverIos& operator =(
        const LineDriverIos&) = delete;

    /* -- line driver interface */
    virtual void skipChars(
        int chars_) override;
    virtual void writeText(
        const char* text_,
        int length_) override;
    virtual void breakLine() override;
    virtual void setFontStyle(
        FontStyle style_) override;
    virtual void setFontWeight(
        FontWeight weight_) override;
    virtual void setForegroundColor(
        Color color_) override;
    virtual void setBackgroundColor(
        Color color_) override;

  private:
    std::ostream* os;
    LineSync sync;
};

} /* -- namespace Typograph */

} /* -- namespace OndraRT */

#endif /* OndraRT__LINEDRIVERIOS_H_ */
