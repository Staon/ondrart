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

#ifndef OndraRT__TYPOGRAPHBLOCK_H_
#define OndraRT__TYPOGRAPHBLOCK_H_

namespace OndraRT {

namespace Typograph {

class LineDriver;
class TypographState;

/**
 * @brief Generic typograph text block
 */
class TypographBlock {
  public:
    struct Border {
      int left;
      int top;
      int right;
      int bottom;

      Border merge(
          const Border& other_) const;
      Border sub(
          const Border& other_) const;
    };

  public:
    TypographBlock();
    virtual ~TypographBlock();

    /* -- avoid copying */
    TypographBlock(
        const TypographBlock&) = delete;
    TypographBlock& operator =(
        const TypographBlock&) = delete;

    /**
     * @brief Write one line
     *
     * @param driver_ An line driver
     * @param width_ Width of the line
     * @param next_width_ Width of next line
     * @param origin_ Origin (from parent's context) typograph state
     */
    virtual void writeLine(
        LineDriver& driver_,
        int width_,
        int next_width_,
        const TypographState& origin_) = 0;

    /**
     * @brief Check whether the whole content of the block is already
     *     printed
     */
    virtual bool isFinished() const noexcept = 0;

    /**
     * @brief Get block's margins
     */
    virtual Border getMargin() const noexcept = 0;
};

} /* -- namespace Typograph */

} /* -- namespace OndraRT */

#endif /* OndraRT__TYPOGRAPHBLOCK_H_ */
