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

#include "typographblocktext.h"

#include <assert.h>
#include <utility>

#include "linedriver.h"

namespace OndraRT {

namespace Typograph {

TypographBlockText::TypographBlockText(
    const std::string& text_) :
  text(text_),
  tokenizer(text.c_str()),
  state(),
  remained_out(0),
  remained_word(),
  prepared_index(0),
  prepared(),
  finished(false) {

}


TypographBlockText::TypographBlockText(
    std::string&& text_) :
  text(std::move(text_)),
  tokenizer(text.c_str()),
  state(),
  remained_out(0),
  remained_word(),
  prepared_index(0),
  prepared(),
  finished(false) {

}

TypographBlockText::~TypographBlockText() {

}

void TypographBlockText::flushPrepared(
    LineDriver& driver_,
    const int width_,
    const int next_width_,
    TypographStateScope& state_,
    int& line_fill_,
    bool line_begin_) {
  /* -- there's nothing to do */
  if(prepared.empty())
    return;

  /* -- Check whether the word can be written on this line. If it can,
   *    continue to print it. If it cannot, check whether it can be
   *    printed at next line. If it can, break current line. */
  if(!line_begin_
      && remained_out == 0
      && line_fill_ + remained_word.length() > width_
      && remained_word.length() < next_width_) {
    driver_.skipChars(width_ - line_fill_);
    line_fill_ = width_;
    return;
  }

  while(prepared_index < prepared.size()) {
    auto& token_(prepared[prepared_index]);
    switch(token_.type) {
      case TypoTokenizer::FONT_STYLE:
        state_.setFontStyle(token_.font_style);
        ++prepared_index;
        break;
      case TypoTokenizer::FONT_WEIGHT:
        state_.setFontWeight(token_.font_weight);
        ++prepared_index;
        break;
      case TypoTokenizer::FOREGROUND:
        state_.setForeground(token_.color);
        ++prepared_index;
        break;
      case TypoTokenizer::BACKGROUND:
        state_.setBackground(token_.color);
        ++prepared_index;
        break;
      case TypoTokenizer::TEXT: {
        if(line_fill_ + token_.length <= width_) {
          /* -- There is enough space, print the word */
          driver_.writeText(
              remained_word.c_str() + remained_out, token_.length);
          ++prepared_index;
          remained_out += token_.length;
          line_fill_ += token_.length;
        }
        else {
          /* -- not enough space */
          int rest_(width_ - line_fill_);
          /* -- break the word */
          driver_.writeText(remained_word.c_str() + remained_out, rest_);
          remained_out += rest_;
          token_.length -= rest_;
          line_fill_ = width_;
          return;
        }
      }
      break;
    }
  }

  /* -- prepare the space after the word */
  if(!prepared.empty() && line_fill_ < width_) {
    driver_.skipChars(1);
    ++line_fill_;
  }

  remained_out = 0;
  remained_word.clear();
  prepared_index = 0;
  prepared.clear();
}

void TypographBlockText::writeLine(
    LineDriver& driver_,
    const int width_,
    const int next_width_,
    const TypographState& origin_) {
  /* -- finished */
  if(isFinished()) {
    driver_.skipChars(width_);
    return;
  }

  /* -- reset device state */
  TypographStateScope state_(&driver_, &origin_, &state);

  /* -- a remaining from previous line */
  int line_fill_(0);
  flushPrepared(driver_, width_, next_width_, state_, line_fill_, true);

  /* -- parse stored text */
  while(line_fill_ < width_) {
    TypoTokenizer::Token token_(tokenizer.nextToken());
    switch(token_.type) {
      case TypoTokenizer::FONT_STYLE:
      case TypoTokenizer::FONT_WEIGHT:
      case TypoTokenizer::FOREGROUND:
      case TypoTokenizer::BACKGROUND:
        prepared.push_back(token_);
        break;
      case TypoTokenizer::TEXT:
        remained_word += token_.text;
        prepared.push_back(token_);
        break;
      case TypoTokenizer::END_OF_TEXT:
        finished = true;
        flushPrepared(driver_, width_, next_width_, state_, line_fill_, false);
        driver_.skipChars(width_ - line_fill_);
        line_fill_ = width_;
        break;
      case TypoTokenizer::SPACE:
        flushPrepared(driver_, width_, next_width_, state_, line_fill_, false);
        break;
      default:
        assert(false);
        break;
    }
  }
}

bool TypographBlockText::isFinished() const noexcept {
  return finished && prepared.empty();
}

TypographBlockText::Border TypographBlockText::getMargin() const noexcept {
  return {0, 0, 0, 0};
}

} /* -- namespace Typograph */

} /* -- namespace OndraRT */
