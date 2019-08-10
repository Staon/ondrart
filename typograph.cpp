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

#include "typograph.h"

#include <assert.h>

#include "linedriver.h"
#include "typographblock.h"
#include "typographstate.h"

namespace OndraRT {

namespace Typograph {

Typograph::Typograph(
    LineDriver* driver_,
    int width_) :
  driver(driver_),
  width(width_) {
  assert(driver != nullptr && width_ > 0);

}

Typograph::~Typograph() {

}

void Typograph::writeBlock(
    TypographBlock& block_) {
  auto margin_(block_.getMargin());

  /* -- print top margin */
  for(int i_(0); i_ < margin_.top; ++i_) {
    driver->skipChars(width);
    driver->breakLine();
  }

  const int box_width_(width - margin_.left - margin_.right);
  TypographState state_;
  while(!block_.isFinished()) {
    /* -- print left margin */
    driver->skipChars(margin_.left);

    /* -- print the line */
    block_.writeLine(*driver, box_width_, box_width_, state_);

    /* -- print right margin */
    driver->skipChars(margin_.right);

    /* -- break the line */
    driver->breakLine();
  }

  /* -- print bottom margin */
  for(int i_(0); i_ < margin_.bottom; ++i_) {
    driver->skipChars(width);
    driver->breakLine();
  }
}

void Typograph::writeEmptyLine() {
  driver->breakLine();
}

} /* -- namespace Typograph */

} /* -- namespace OndraRT */
