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

#include "typotokenizer.h"

#include <assert.h>
#include <cctype>

#include "typoerror.h"

namespace OndraRT {

namespace Typograph {

TypoTokenizer::TypoTokenizer(
    const char* text_) :
  text(text_),
  current(text_),
  buffer(),
  font_style(LineDriver::FS_DEFAULT),
  font_weight(LineDriver::FW_DEFAULT) {
  assert(text != nullptr && current != nullptr);

}

TypoTokenizer::~TypoTokenizer() {

}

TypoTokenizer::Token TypoTokenizer::finishBuffer() {
  Token token_;
  token_.type = TEXT;
  token_text = buffer.str();
  buffer.str("");
  token_.text = token_text.c_str();
  token_.length = token_text.length();
  return token_;
}

TypoTokenizer::Token TypoTokenizer::handleTag() {
  Token token_;

  if(token_text == "fg") {
    token_.type = FOREGROUND;
    token_.color = parseColor(buffer.str());
  }
  else if(token_text == "bg") {
    token_.type = BACKGROUND;
    token_.color = parseColor(buffer.str());
  }
  else {
    throw TypoError("invalid tag '" + token_text + "'");
  }

  return token_;
}

LineDriver::Color TypoTokenizer::parseColor(
    const std::string& value_) {
  if (value_ == "")
    return LineDriver::C_DEFAULT;
  if (value_ == "white")
    return LineDriver::C_WHITE;
  if (value_ == "black")
    return LineDriver::C_BLACK;
  if (value_ == "red")
    return LineDriver::C_RED;
  if (value_ == "green")
    return LineDriver::C_GREEN;
  if (value_ == "yellow")
    return LineDriver::C_YELLOW;
  if (value_ == "blue")
    return LineDriver::C_BLUE;
  if (value_ == "magenta")
    return LineDriver::C_MAGENTA;
  if (value_ == "cyan")
    return LineDriver::C_CYAN;

  throw TypoError("invalid color value '" + value_ +"'");
}

TypoTokenizer::Token TypoTokenizer::nextToken() {
  Token token_;

  buffer.str("");
  enum State {
    S_BEGIN,
    S_SPACE,
    S_TEXT,
    S_ESCAPED,
    S_ATTRIBUTE,
    S_ATTRIBUTE2,
    S_TAG,
    S_VALUE,
    S_TAG_END,
  } state_(S_BEGIN);
  for(; ; ++current) {
    switch(state_) {
      case S_BEGIN:
        switch(*current) {
          case 0:
            token_.type = END_OF_TEXT;
            return token_;
          case '\\':
            state_ = S_ESCAPED;
            break;
          case '*':
            state_ = S_ATTRIBUTE;
            break;
          case '#':
            state_ = S_TAG;
            break;
          default:
            if(std::isspace(*current)) {
              state_ = S_SPACE;
            }
            else {
              buffer.put(*current);
              state_ = S_TEXT;
            }
            break;
        }
        break;

      case S_SPACE:
        switch(*current) {
          case '0':
            token_.type = SPACE;
            return token_;
          default:
            if(!std::isspace(*current)) {
              token_.type = SPACE;
              return token_;
            }
            break;
        }
        break;

      case S_TEXT:
        switch(*current) {
          case 0:
          case '*':
          case '#':
            return finishBuffer();
          case '\\':
            state_ = S_ESCAPED;
            break;
          default:
            if(std::isspace(*current))
              return finishBuffer();
            else
              buffer.put(*current);
            break;
        }
        break;

      case S_ESCAPED:
        if(*current == 0)
          throw TypoError("escape sequence at the end of the string");
        buffer.put(*current);
        state_ = S_TEXT;
        break;

      case S_ATTRIBUTE:
        if(*current == '*')
          state_ = S_ATTRIBUTE2;
        else {
          token_.type = FONT_STYLE;
          if(font_style == LineDriver::FS_DEFAULT)
            token_.font_style = font_style = LineDriver::FS_ITALIC;
          else
            token_.font_style = font_style = LineDriver::FS_DEFAULT;
          return token_;
        }
        break;

      case S_ATTRIBUTE2:
        token_.type = FONT_WEIGHT;
        if(font_weight == LineDriver::FW_DEFAULT)
          token_.font_weight = font_weight = LineDriver::FW_BOLD;
        else
          token_.font_weight = font_weight = LineDriver::FW_DEFAULT;
        return token_;

      case S_TAG:
        switch(*current) {
          case 0:
            throw TypoError("invalid tag at the end of the string");
          case ':':
            token_text = buffer.str();
            buffer.str("");
            state_ = S_VALUE;
            break;
          case '#':
            token_text = buffer.str();
            buffer.str("");
            state_ = S_TAG_END;
            break;
          default:
            buffer.put(*current);
            break;
        }
        break;

      case S_VALUE:
        switch(*current) {
          case 0:
            throw TypoError("invalid tag at the end of the string");
          case '#':
            state_ = S_TAG_END;
            break;
          default:
            buffer.put(*current);
            break;
        }
        break;

      case S_TAG_END:
        return handleTag();
    }
  }
}

} /* -- namespace Typograph */

} /* -- namespace OndraRT */
