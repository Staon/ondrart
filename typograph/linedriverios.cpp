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

#include "linedriverios.h"

#include <assert.h>
#include <iostream>

namespace OndraRT {

namespace Typograph {

LineDriverIos::LineDriverIos(
    std::ostream* os_,
    LineSync sync_) :
  os(os_),
  sync(sync_) {
  assert(os != nullptr);

}

LineDriverIos::~LineDriverIos() {

}

void LineDriverIos::skipChars(
    int chars_) {
  for(int i_(0); i_ < chars_; ++i_)
    os->put(' ');
}

void LineDriverIos::writeText(
    const char* text_,
    int length_) {
  assert(text_ != nullptr && length_ >= 0);
  os->write(text_, length_);
}

void LineDriverIos::breakLine() {
  if(sync == SYNC)
    *os << std::endl;
  else
    *os << '\n';
}

void LineDriverIos::setFontStyle(
    FontStyle style_) {
  /* -- not supported */
}

void LineDriverIos::setFontWeight(
    FontWeight weight_) {
  /* -- not supported */
}

void LineDriverIos::setForegroundColor(
    Color color_) {
  /* -- not supported */
}

void LineDriverIos::setBackgroundColor(
    Color color_) {
  /* -- not supported */
}

} /* -- namespace Typograph */

} /* -- namespace OndraRT */
