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

#include "typographstate.h"

#include <algorithm>
#include <assert.h>

#include "linedriver.h"

namespace OndraRT {

namespace Typograph {

TypographState::TypographState() :
  font_style(LineDriver::FS_DEFAULT),
  font_weight(LineDriver::FW_DEFAULT),
  foreground(LineDriver::C_DEFAULT),
  background(LineDriver::C_DEFAULT) {

}

TypographState::TypographState(
    LineDriver::FontStyle font_style_,
    LineDriver::FontWeight font_weight_,
    LineDriver::Color foreground_,
    LineDriver::Color background_) :
  font_style(font_style_),
  font_weight(font_weight_),
  foreground(foreground_),
  background(background_) {

}

TypographState::TypographState(
    const TypographState& other_) :
  font_style(other_.font_style),
  font_weight(other_.font_weight),
  foreground(other_.foreground),
  background(other_.background) {

}

TypographState::~TypographState() {

}

void TypographState::swap(
    TypographState& other_) noexcept {
  std::swap(font_style, other_.font_style);
  std::swap(font_weight, other_.font_weight);
  std::swap(foreground, other_.foreground);
  std::swap(background, other_.background);
}

TypographState& TypographState::operator =(
    const TypographState& other_) {
  TypographState tmp_(other_);
  swap(tmp_);
  return *this;
}

TypographStateScope::TypographStateScope(
    LineDriver* driver_,
    const TypographState* origin_,
    TypographState* scope_) :
  driver(driver_),
  origin(origin_),
  scope(scope_) {
  assert(driver != nullptr && origin != nullptr && scope != nullptr);

  /* -- merge values */
  if(scope->font_style == LineDriver::FS_DEFAULT)
    merged.font_style = origin->font_style;
  else
    merged.font_style = scope->font_style;
  if(scope->font_weight == LineDriver::FW_DEFAULT)
    merged.font_weight = origin->font_weight;
  else
    merged.font_weight = scope->font_weight;
  if(scope->foreground == LineDriver::C_DEFAULT)
    merged.foreground = origin->foreground;
  else
    merged.foreground = scope->foreground;
  if(scope->background == LineDriver::C_DEFAULT)
    merged.background = origin->background;
  else
    merged.background = scope->background;

  /* -- change the driver */
  if(merged.font_style != origin->font_style)
    driver->setFontStyle(merged.font_style);
  if(merged.font_weight != origin->font_weight)
    driver->setFontWeight(merged.font_weight);
  if(merged.foreground != origin->foreground)
    driver->setForegroundColor(merged.foreground);
  if(merged.background != origin->background)
    driver->setBackgroundColor(merged.background);
}

TypographStateScope::~TypographStateScope() {
  /* -- reset previous state */
  if(merged.font_style != origin->font_style)
    driver->setFontStyle(origin->font_style);
  if(merged.font_weight != origin->font_weight)
    driver->setFontWeight(origin->font_weight);
  if(merged.foreground != origin->foreground)
    driver->setForegroundColor(origin->foreground);
  if(merged.background != origin->background)
    driver->setBackgroundColor(origin->background);
}

const TypographState& TypographStateScope::getState() const noexcept {
  return merged;
}

void TypographStateScope::setFontStyle(
    LineDriver::FontStyle style_) {
  if(style_ != scope->font_style) {
    scope->font_style = style_;
    if(style_ == LineDriver::FS_DEFAULT)
      merged.font_style = origin->font_style;
    else
      merged.font_style = style_;
    driver->setFontStyle(merged.font_style);
  }
}

void TypographStateScope::setFontWeight(
    LineDriver::FontWeight weight_) {
  if(weight_ != scope->font_weight) {
    scope->font_weight = weight_;
    if(weight_ == LineDriver::FW_DEFAULT)
      merged.font_weight = origin->font_weight;
    else
      merged.font_weight = weight_;
    driver->setFontWeight(merged.font_weight);
  }
}

void TypographStateScope::setForeground(
    LineDriver::Color color_) {
  if(scope->foreground != color_) {
    scope->foreground = color_;
    if(color_ == LineDriver::C_DEFAULT)
      merged.foreground = origin->foreground;
    else
      merged.foreground = color_;
    driver->setForegroundColor(merged.foreground);
  }
}

void TypographStateScope::setBackground(
    LineDriver::Color color_) {
  if(scope->background != color_) {
    scope->background = color_;
    if(color_ == LineDriver::C_DEFAULT)
      merged.background = origin->background;
    else
      merged.background = color_;
    driver->setBackgroundColor(merged.background);
  }
}

} /* -- namespace Typograph */

} /* -- namespace OndraRT */
