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

#include "typographblockbox.h"

#include <assert.h>

#include "linedriver.h"
#include "typoerror.h"

namespace OndraRT {

namespace Typograph {

TypographBlockBox::TypographBlockBox(
    TypographBlock* block_,
    int margin_) :
  block(block_),
  margin{margin_, margin_, margin_, margin_},
  padding{0, 0, 0, 0},
  current_top(0),
  current_bottom(0) {
  assert(block != nullptr);

}

TypographBlockBox::TypographBlockBox(
    TypographBlock* block_,
    int left_,
    int top_,
    int right_,
    int bottom_) :
  block(block_),
  margin{left_, top_, right_, bottom_},
  padding{0, 0, 0, 0},
  current_top(0),
  current_bottom(0) {
  assert(block != nullptr);

}

TypographBlockBox::TypographBlockBox(
    TypographBlock* block_,
    const Border& margin_) :
  block(block_),
  margin(margin_),
  padding{0, 0, 0, 0},
  current_top(0),
  current_bottom(0) {
  assert(block != nullptr);

}

TypographBlockBox::~TypographBlockBox() {

}

void TypographBlockBox::setPadding(
    int padding_) {
  padding = {padding_, padding_, padding_, padding_};
  current_top = current_top = padding_;
}

void TypographBlockBox::setPadding(
    const Border& padding_) {
  padding = padding_;
  current_top = padding.top;
  current_bottom = padding.bottom;
}

void TypographBlockBox::setPadding(
    int left_,
    int top_,
    int right_,
    int bottom_) {
  padding = {left_, top_, right_, bottom_};
  current_top = padding.top;
  current_bottom = padding.bottom;
}

void TypographBlockBox::writeLine(
    LineDriver& driver_,
    int width_,
    int next_width_,
    const TypographState& origin_) {
  /* -- print top padding */
  if (current_top > 0) {
    driver_.skipChars(width_);
    --current_top;
    return;
  }

  if (!block->isFinished()) {
    auto nested_width_(width_ - padding.left - padding.right);
    if (nested_width_ < 1)
      throw TypoError("there is not enough space to print the box");
    auto nested_width_next_(next_width_ - padding.left - padding.right);
    if (nested_width_next_ < 1)
      throw TypoError("there is not enough space to print the box");
    driver_.skipChars(padding.left);
    block->writeLine(
        driver_, nested_width_, nested_width_next_, origin_);
    driver_.skipChars(padding.right);
    return;
  }

  /* -- print bottom padding */
  if (current_bottom > 0) {
    driver_.skipChars(width_);
    --current_bottom;
    return;
  }

  /* -- the box is finished, just skip characters */
  driver_.skipChars(width_);
}

bool TypographBlockBox::isFinished() const noexcept {
  return current_top <= 0 && current_bottom <= 0 && block->isFinished();
}

TypographBlockBox::Border TypographBlockBox::getMargin() const noexcept {
  return margin.merge(block->getMargin().sub(padding));
}

} /* -- namespace Typograph */

} /* -- namespace OndraRT */
