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

#include "typographblock.h"

namespace OndraRT {

namespace Typograph {

TypographBlock::Margin TypographBlock::Margin::merge(
    const TypographBlock::Margin& other_) const {
  return {
    (left < other_.left) ? other_.left : left,
    (top < other_.top) ? other_.top : top,
    (right < other_.right) ? other_.right : right,
    (bottom < other_.bottom) ? other_.bottom : bottom,
  };
}

TypographBlock::TypographBlock() {

}

TypographBlock::~TypographBlock() {

}

} /* -- namespace Typograph */

} /* -- namespace OndraRT */
