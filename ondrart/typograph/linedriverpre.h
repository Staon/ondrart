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

#ifndef OndraRT__LINEDRIVERPRE_H_
#define OndraRT__LINEDRIVERPRE_H_

#include <iosfwd>

#include <ondrart/typograph/linedriver.h>

namespace OndraRT {

namespace Typograph {

/**
 * @brief A line driver generating content of the HTML <pre> tag
 */
class LineDriverPre : public LineDriver {
  public:
    /**
     * @brief Ctor
     *
     * @param os_ An output stream. The ownership is not taken.
     */
    explicit LineDriverPre(
        std::ostream* os_);

    /**
     * @brief Dtor
     */
    virtual ~LineDriverPre();

    /* -- line driver */
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
    void printColor(
        const char* style_,
        Color color_);
    void openSpan();
    void closeSpan();

    std::ostream* os;
    bool opened_span;
    bool changed_attributes;
    FontStyle font_style;
    FontWeight font_weight;
    Color foreground;
    Color background;
};

} /* -- namespace Typograph */

} /* -- namespace OndraRT */

#endif /* OndraRT__LINEDRIVERPRE_H_ */
