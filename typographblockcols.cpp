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

#include "typographblockcols.h"

#include <algorithm>
#include "assert.h"

#include "linedriver.h"
#include "typoerror.h"

namespace OndraRT {

namespace Typograph {

TypographBlockCols::TypographBlockCols(
    const Column* columns_,
    int colsnum_) :
  columns(columns_),
  colsnum(colsnum_) {
  assert(columns != nullptr && colsnum > 0);

}

TypographBlockCols::~TypographBlockCols() {

}

void TypographBlockCols::writeLine(
    LineDriver& driver_,
    int width_,
    int next_width_,
    const TypographState& origin_) {
  /* -- compute widths of columns */
  int fixed_sum_(0);
  int var_count_(0);
  int inner_space_(0);
  int margin_(0);
  for(int i_(0); i_ < colsnum; ++i_) {
    if(columns[i_].width <= 0)
      ++var_count_;
    else
      fixed_sum_ += columns[i_].width;

    auto block_margin_(columns[i_].block->getMargin());
    if(i_ > 0) {
      if(margin_ > block_margin_.left)
        inner_space_ += margin_;
      else
        inner_space_ += block_margin_.left;
    }
    margin_ = block_margin_.right;
  }

  /* -- requested columns are too wide */
  int allocated_(inner_space_ + fixed_sum_);
  if(allocated_ + var_count_ > width_)
    throw TypoError("cannot solve column widths");
  if(allocated_ + var_count_ > next_width_)
    throw TypoError("cannot solve column widths for next line");

  /* -- solve variable widths */
  int var_space_(width_ - allocated_);
  int var_space_next_(next_width_ - allocated_);
  int var_width_(0);
  int var_width_next_(0);
  if(var_count_ > 0) {
    var_width_ = var_space_ / var_count_;
    var_width_next_ = var_space_next_ / var_count_;
    allocated_ = width_;
  }

  margin_ = 0;
  bool var_first_(true);
  for(int i_(0); i_ < colsnum; ++i_) {
    /* -- left margin */
    auto block_margin_(columns[i_].block->getMargin());
    if(i_ > 0) {
      if(block_margin_.left > margin_)
        margin_ = block_margin_.left;
      driver_.skipChars(margin_);
    }

    /* -- print the text */
    int col_width_(columns[i_].width);
    int col_width_next_(col_width_);
    if(col_width_ <= 0) {
      if(var_first_) {
        /* -- correction of integer rounding */
        col_width_ = var_space_ - (var_count_ - 1) * var_width_;
        col_width_next_ = var_space_next_ - (var_count_ - 1) * var_width_next_;
        var_first_ = false;
      }
      else {
        col_width_ = var_width_;
        col_width_next_ = var_width_next_;
      }
    }
    columns[i_].block->writeLine(
        driver_, col_width_, col_width_next_, origin_);

    /* -- prepare next margin */
    margin_ = block_margin_.right;
  }

  if(allocated_ < width_)
    driver_.skipChars(width_ - allocated_);
}

bool TypographBlockCols::isFinished() const noexcept {
  return std::all_of(
      columns,
      columns + colsnum,
      [](const Column& col){ return col.block->isFinished();});
}

TypographBlockCols::Margin TypographBlockCols::getMargin() const noexcept {
  int left_(columns[0].block->getMargin().left);
  int right_(columns[colsnum - 1].block->getMargin().right);
  int top_(0);
  int bottom_(0);
  for(int i_(0); i_ < colsnum; ++i_) {
    auto margin_(columns[i_].block->getMargin());
    if(margin_.top > top_)
      top_ = margin_.top;
    if(margin_.bottom > bottom_)
      bottom_ = margin_.bottom;
  }
  return {left_, top_, right_, bottom_};
}

} /* -- namespace Typograph */

} /* -- namespace OndraRT */
