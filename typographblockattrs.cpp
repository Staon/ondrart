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

#include "typographblockattrs.h"

namespace OndraRT {

namespace Typograph {

TypographBlockAttrs::TypographBlockAttrs(
    TypographBlock* block_,
    LineDriver::FontStyle font_style_,
    LineDriver::FontWeight font_weight_,
    LineDriver::Color foreground_,
    LineDriver::Color background_) :
  block(block_),
  state(font_style_, font_weight_, foreground_, background_) {

}

TypographBlockAttrs::~TypographBlockAttrs() {

}

void TypographBlockAttrs::writeLine(
    LineDriver& driver_,
    int width_,
    int next_width_,
    const TypographState& origin_) {
  TypographStateScope scope_(&driver_, &origin_, &state);
  block->writeLine(driver_, width_, next_width_, scope_.getState());
}

bool TypographBlockAttrs::isFinished() const noexcept {
  return block->isFinished();
}

TypographBlockAttrs::Border TypographBlockAttrs::getMargin() const noexcept {
  return block->getMargin();
}

} /* -- namespace Typograph */

} /* -- namespace OndraRT */
