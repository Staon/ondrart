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

#ifndef OndraRT__TYPOTOKENIZER_H_
#define OndraRT__TYPOTOKENIZER_H_

#include "linedriver.h"

#include <sstream>
#include <string>

namespace OndraRT {

namespace Typograph {

/**
 * @brief Tokenizer of a text
 *
 * This class breaks a text into a stream of tokens. The tokenizer supports
 * special tags changing text attributes or text colors.
 */
class TypoTokenizer {
  public:
    enum TokenType {
      END_OF_TEXT,
      SPACE,
      TEXT,
      FONT_STYLE,
      FONT_WEIGHT,
      FOREGROUND,
      BACKGROUND,
    };

    struct Token {
        TokenType type;
        union {
            struct {
                const char* text;
                int length;
            };
            LineDriver::FontStyle font_style;
            LineDriver::FontWeight font_weight;
            LineDriver::Color color;
        };
    };

  public:
    /**
     * @brief Ctor
     *
     * @param text_ The text which the tokenizer will be parsing. The ownership
     *     is not taken.
     */
    explicit TypoTokenizer(
        const char* text_);

    /**
     * @brief Dtor
     */
    ~TypoTokenizer();

    /**
     * @brief Get next token
     */
    Token nextToken();

  private:
    Token finishBuffer();
    Token handleTag();
    LineDriver::Color parseColor(
        const std::string& value_);

    const char* text;
    const char* current;
    std::ostringstream buffer;
    std::string token_text;
    LineDriver::FontStyle font_style;
    LineDriver::FontWeight font_weight;
};

} /* -- namespace Typograph */

} /* -- namespace OndraRT */

#endif /* OndraRT__TYPOTOKENIZER_H_ */
