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

namespace OndraRT {

namespace Typograph {

TypographBlockBox::TypographBlockBox(
    TypographBlock* block_,
    int margin_) :
  block(block_),
  margin{margin_, margin_, margin_, margin_} {
  assert(block != nullptr);

}

TypographBlockBox::TypographBlockBox(
    TypographBlock* block_,
    int left_,
    int top_,
    int right_,
    int bottom_) :
  block(block_),
  margin{left_, top_, right_, bottom_} {
  assert(block != nullptr);

}

TypographBlockBox::TypographBlockBox(
    TypographBlock* block_,
    const Margin& margin_) :
  block(block_),
  margin(margin_) {
  assert(block != nullptr);

}

TypographBlockBox::~TypographBlockBox() {

}

void TypographBlockBox::writeLine(
    LineDriver& driver_,
    int width_,
    int next_width_,
    const TypographState& origin_) {
  return block->writeLine(driver_, width_, next_width_, origin_);
}

bool TypographBlockBox::isFinished() const noexcept {
  return block->isFinished();
}

TypographBlockBox::Margin TypographBlockBox::getMargin() const noexcept {
  return margin.merge(block->getMargin());
}

} /* -- namespace Typograph */

} /* -- namespace OndraRT */
