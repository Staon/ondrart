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

#ifndef OndraRT__TYPOGRAPHBLOCKATTRS_H_
#define OndraRT__TYPOGRAPHBLOCKATTRS_H_

#include "linedriver.h"
#include "typographblock.h"
#include "typographstate.h"

namespace OndraRT {

namespace Typograph {

/**
 * @brief A simple block keeping text attributes
 */
class TypographBlockAttrs : public TypographBlock {
  public:
    /**
     * @brief Ctor
     *
     * @param block_ Nested block. The ownership is not taken.
     * @param font_style_ Font style
     * @param font_weight_ Font weight
     * @param foreground_ Foreground color
     * @param background_ Background color
     */
    explicit TypographBlockAttrs(
        TypographBlock* block_,
        LineDriver::FontStyle font_style_,
        LineDriver::FontWeight font_weight_,
        LineDriver::Color foreground_,
        LineDriver::Color background_);

    /**
     * @brief Dtor
     */
    virtual ~TypographBlockAttrs();

    /* -- avoid copying */
    TypographBlockAttrs(
        const TypographBlockAttrs&) = delete;
    TypographBlockAttrs& operator =(
        const TypographBlockAttrs&) = delete;

    /* -- typograph block */
    virtual void writeLine(
        LineDriver& driver_,
        int width_,
        int next_width_,
        const TypographState& origin_) override;
    virtual bool isFinished() const noexcept override;
    virtual Margin getMargin() const noexcept override;

  private:
    TypographBlock* block;
    TypographState state;
};

} /* -- namespace Typograph */

} /* -- namespace OndraRT */

#endif /* OndraRT__TYPOGRAPHBLOCKATTRS_H_ */
