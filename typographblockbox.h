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

#ifndef OndraRT__TYPOGRAPHBLOCKBOX_H_
#define OndraRT__TYPOGRAPHBLOCKBOX_H_

#include "typographblock.h"

namespace OndraRT {

namespace Typograph {

/**
 * @brief Simple block just keeping margins
 */
class TypographBlockBox : public TypographBlock {
  public:
    explicit TypographBlockBox(
        TypographBlock* block_,
        int margin_);
    explicit TypographBlockBox(
        TypographBlock* block_,
        int left_,
        int top_,
        int right_,
        int bottom_);
    explicit TypographBlockBox(
        TypographBlock* block_,
        const Margin& margin_);

    virtual ~TypographBlockBox();

    /* -- avoid copying */
    TypographBlockBox(
        const TypographBlockBox&) = delete;
    TypographBlockBox& operator =(
        const TypographBlockBox&) = delete;

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
    Margin margin;
};

} /* -- namespace Typograph */

} /* -- namespace OndraRT */

#endif /* OndraRT__TYPOGRAPHBLOCKBOX_H_ */
