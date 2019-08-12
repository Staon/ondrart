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

#ifndef OndraRT__TYPOGRAPHBLOCKPAR_H_
#define OndraRT__TYPOGRAPHBLOCKPAR_H_

#include "typographblock.h"

namespace OndraRT {

namespace Typograph {

/**
 * @brief Paragraph of a text
 */
class TypographBlockPar : public TypographBlock {
  public:
    /**
     * @brief Ctor
     *
     * @param block_ Text of the paragraph
     * @param first_indent_ Indentation of the first line (>= 0)
     * @param indent_ Indentation of following lines (>= 0)
     */
    explicit TypographBlockPar(
        TypographBlock* block_,
        int first_indent_,
        int indent_);

    /**
     * @brief Dtor
     */
    virtual ~TypographBlockPar();

    /* -- avoid copying */
    TypographBlockPar(
        const TypographBlockPar&) = delete;
    TypographBlockPar& operator =(
        const TypographBlockPar&) = delete;

    /* -- typograph block */
    virtual void writeLine(
        LineDriver& driver_,
        int width_,
        int next_width_,
        const TypographState& origin_) override;
    virtual bool isFinished() const noexcept override;
    virtual Border getMargin() const noexcept override;

  private:
    TypographBlock* block;
    int first_indent;
    int indent;
    bool first_line;
};

} /* -- namespace Typograph */

} /* -- namespace OndraRT */

#endif /* OndraRT__TYPOGRAPHBLOCKPAR_H_ */
