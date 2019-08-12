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

#ifndef OndraRT__TYPOGRAPHBLOCKSEQ_H_
#define OndraRT__TYPOGRAPHBLOCKSEQ_H_

#include "typographblock.h"

namespace OndraRT {

namespace Typograph {

/**
 * @brief Sequential container
 *
 * This container prints blocks sequentially and vertically.
 */
class TypographBlockSeq : public TypographBlock {
  public:
    /**
     * @brief Ctor
     *
     * @param blocks_ Array of blocks
     * @param blocks_num_ Number of blocks
     */
    explicit TypographBlockSeq(
        TypographBlock** blocks_,
        int blocks_num_);

    virtual ~TypographBlockSeq();

    /* -- avoid copying */
    TypographBlockSeq(
        const TypographBlockSeq&) = delete;
    TypographBlockSeq& operator =(
        const TypographBlockSeq&) = delete;

    /* -- typograph block */
    virtual void writeLine(
        LineDriver& driver_,
        int width_,
        int next_width_,
        const TypographState& origin_) override;
    virtual bool isFinished() const noexcept override;
    virtual Border getMargin() const noexcept override;

  public:
    TypographBlock** blocks;
    int blocks_num;
    int current_block;
    int current_space;
};

} /* -- namespace Typograph */

} /* -- namespace OndraRT */

#endif /* OndraRT__TYPOGRAPHBLOCKSEQ_H_ */
