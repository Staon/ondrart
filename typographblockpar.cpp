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

#include "typographblockpar.h"

#include "assert.h"

#include "linedriver.h"

namespace OndraRT {

namespace Typograph {

TypographBlockPar::TypographBlockPar(
    TypographBlock* block_,
    int first_indent_,
    int indent_) :
  block(block_),
  first_indent(first_indent_),
  indent(indent_),
  first_line(true) {
  assert(block != nullptr && first_indent >= 0 && indent >= 0);

}

TypographBlockPar::~TypographBlockPar() {

}

void TypographBlockPar::writeLine(
    LineDriver& driver_,
    int width_,
    int next_width_,
    const TypographState& origin_) {

  /* -- select indentation */
  int curr_indent_;
  if(first_line)
    curr_indent_ = first_indent;
  else
    curr_indent_ = indent;
  first_line = false;

  /* -- if the indentation is too big, make it zero */
  if(curr_indent_ >= width_)
    curr_indent_ = 0;

  /* -- indentation of next line */
  int next_indent_(indent);
  if(next_indent_ >= next_width_)
    next_indent_ = 0;

  /* -- skip current indentation */
  driver_.skipChars(curr_indent_);

  /* -- print the line of the text */
  block->writeLine(
      driver_, width_ - curr_indent_, next_width_ - next_indent_, origin_);
}

bool TypographBlockPar::isFinished() const noexcept {
  return block->isFinished();
}

TypographBlockPar::Margin TypographBlockPar::getMargin() const noexcept {
  return {0, 0, 0, 0};
}


} /* -- namespace Typograph */

} /* -- namespace OndraRT */
