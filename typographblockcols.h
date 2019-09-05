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

#ifndef OndraRT__TYPOGRAPHBLOCKCOLS_H_
#define OndraRT__TYPOGRAPHBLOCKCOLS_H_

#include "typographblock.h"

#include <vector>

namespace OndraRT {

namespace Typograph {

/**
 * @brief Formatting of several text columns
 */
class TypographBlockCols : public TypographBlock {
  public:
    struct Column {
      TypographBlock* block;
      int width;
    };

  public:
    /**
     * @brief Ctor
     *
     * @param columns_ Array of columns. The ownership is not taken.
     * @param colsnum_ Number of columns
     */
    explicit TypographBlockCols(
        const Column* columns_,
        int colsnum_);

    /**
     * @brief Dtor
     */
    virtual ~TypographBlockCols();

    /* -- avoid copying */
    TypographBlockCols(
        const TypographBlockCols&) = delete;
    TypographBlockCols& operator =(
        const TypographBlockCols&) = delete;

    /* -- typograph block */
    virtual void writeLine(
        LineDriver& driver_,
        int width_,
        int next_width_,
        const TypographState& origin_) override;
    virtual bool isFinished() const noexcept override;
    virtual Border getMargin() const noexcept override;

  private:
    std::vector<Column> columns;
};

} /* -- namespace Typograph */

} /* -- namespace OndraRT */

#endif /* OndraRT__TYPOGRAPHBLOCKCOLS_H_ */
