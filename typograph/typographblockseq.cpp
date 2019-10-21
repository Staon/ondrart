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

#include "typographblockseq.h"

#include <assert.h>

#include "linedriver.h"

namespace OndraRT {

namespace Typograph {

TypographBlockSeq::TypographBlockSeq(
    TypographBlock** blocks_,
    int blocks_num_) :
  blocks(blocks_),
  blocks_num(blocks_num_),
  current_block(0),
  current_space(0) {
  assert(blocks != nullptr && blocks_num > 0);

}

TypographBlockSeq::~TypographBlockSeq() {

}

void TypographBlockSeq::writeLine(
    LineDriver& driver_,
    int width_,
    int next_width_,
    const TypographState& origin_) {
  /* -- print margin between blocks */
  if(current_space > 0) {
    driver_.skipChars(width_);
    --current_space;
    return;
  }

  /* -- give the chance to the block */
  if(current_block < blocks_num) {
    TypographBlock* block_(blocks[current_block]);

    /* -- print the line */
    block_->writeLine(driver_, width_, next_width_, origin_);

    /* -- move to next block */
    if(block_->isFinished()) {
      ++current_block;
      current_space = block_->getMargin().bottom;
      if (current_block < blocks_num) {
        auto top_(blocks[current_block]->getMargin().top);
        if(top_ > current_space)
          current_space = top_;
      }
    }
  }
}

bool TypographBlockSeq::isFinished() const noexcept {
  return current_block >= blocks_num;
}

TypographBlockSeq::Border TypographBlockSeq::getMargin() const noexcept {
  int top_(blocks[0]->getMargin().top);
  int bottom_(blocks[blocks_num - 1]->getMargin().bottom);
  int left_(0);
  int right_(0);
  for(int i_(0); i_ < blocks_num; ++i_) {
    auto margin_(blocks[i_]->getMargin());
    if(margin_.left > left_)
      left_ = margin_.left;
    if(margin_.right > right_)
      right_ = margin_.right;
  }
  return {left_, top_, right_, bottom_};
}

} /* -- namespace Typograph */

} /* -- namespace OndraRT */
