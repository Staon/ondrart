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

#ifndef OndraRT__TYPOGRAPHBLOCKTEXT_H_
#define OndraRT__TYPOGRAPHBLOCKTEXT_H_

#include <string>
#include <vector>

#include "typographblock.h"
#include "typographstate.h"
#include "typotokenizer.h"

namespace OndraRT {

namespace Typograph {

/**
 * @brief A typograph block formatting specified text into a block
 */
class TypographBlockText : public TypographBlock {
  public:
    /**
     * @brief Ctor
     *
     * @param text_ The specified text
     */
    explicit TypographBlockText(
        const std::string& text_);
    explicit TypographBlockText(
        std::string&& text_);

    /**
     * @brief Dtor
     */
    virtual ~TypographBlockText();

    /* -- avoid copying */
    TypographBlockText(
        const TypographBlockText&) = delete;
    TypographBlockText& operator =(
        const TypographBlockText&) = delete;

    /* -- typograph block */
    virtual void writeLine(
        LineDriver& driver_,
        int width_,
        int next_width_,
        const TypographState& origin_);
    bool isFinished() const noexcept;
    virtual Border getMargin() const noexcept override;

  private:
    void flushPrepared(
        LineDriver& driver_,
        int width_,
        int next_width_,
        TypographStateScope& state_,
        int& line_fill_,
        bool line_begin_);

    std::string text;
    TypoTokenizer tokenizer;
    TypographState state;

    /* -- prepared sequence of formatting commands */
    int remained_out;
    std::string remained_word;
    int prepared_index;
    std::vector<TypoTokenizer::Token> prepared;

    bool finished;
};

} /* -- namespace Typograph */

} /* -- namespace OndraRT */

#endif /* OndraRT__TYPOGRAPHBLOCKTEXT_H_ */
