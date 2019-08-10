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

#include "linedriverpre.h"

#include <assert.h>
#include <iostream>

namespace OndraRT {

namespace Typograph {

LineDriverPre::LineDriverPre(
    std::ostream* os_) :
  os(os_),
  opened_span(false),
  changed_attributes(false),
  font_style(FS_DEFAULT),
  font_weight(FW_DEFAULT),
  foreground(C_DEFAULT),
  background(C_DEFAULT) {
  assert(os != nullptr);

}

LineDriverPre::~LineDriverPre() {

}

void LineDriverPre::skipChars(
    int chars_) {
  openSpan();
  for(int i_(0); i_ < chars_; ++i_)
    os->put(' ');
}

void LineDriverPre::writeText(
    const char* text_,
    int length_) {
  openSpan();
  os->write(text_, length_);
}

void LineDriverPre::breakLine() {
  closeSpan();
  os->put('\n');
}

void LineDriverPre::printColor(
    const char* style_,
    Color color_) {
  if(color_ != C_DEFAULT) {
    *os << style_ << ':';
    switch(color_) {
      case C_BLACK:
        *os << "black";
        break;
      case C_RED:
        *os << "red";
        break;
      case C_GREEN:
        *os << "green";
        break;
      case C_YELLOW:
        *os << "yellow";
        break;
      case C_BLUE:
        *os << "blue";
        break;
      case C_MAGENTA:
        *os << "magenta";
        break;
      case C_CYAN:
        *os << "cyan";
        break;
      case C_WHITE:
        *os << "white";
        break;
      default:
        assert(false);
        *os << "black";
        break;
    }
    *os << ';';
  }
}

void LineDriverPre::openSpan() {
  if(changed_attributes) {
    closeSpan();

    if(font_style != FS_DEFAULT || font_weight != FW_DEFAULT
        || foreground != C_DEFAULT || background != C_DEFAULT) {
      *os << "<span style=\"";

      if(font_style != FS_DEFAULT) {
        *os << "font-style:";
        switch(font_style) {
          case FS_NORMAL:
            *os << "normal";
            break;
          case FS_ITALIC:
            *os << "italic";
            break;
          default:
            assert(false);
            break;
        }
        *os << ';';
      }

      if(font_weight != FW_DEFAULT) {
        *os << "font-weight:";
        switch(font_weight) {
          case FW_NORMAL:
            *os << "normal";
            break;
          case FW_BOLD:
            *os << "bold";
            break;
          default:
            assert(false);
            break;
        }
        *os << ';';
      }

      printColor("color", foreground);
      printColor("background-color", background);

      *os << "\">";
      opened_span = true;
      changed_attributes = false;
    }
  }
}

void LineDriverPre::closeSpan() {
  if(opened_span) {
    *os << "</span>";
    opened_span = false;
  }
}

void LineDriverPre::setFontStyle(
    FontStyle style_) {
  font_style = style_;
  changed_attributes = true;
}

void LineDriverPre::setFontWeight(
    FontWeight weight_) {
  font_weight = weight_;
  changed_attributes = true;
}

void LineDriverPre::setForegroundColor(
    Color color_) {
  foreground = color_;
  changed_attributes = true;
}

void LineDriverPre::setBackgroundColor(
    Color color_) {
  background = color_;
  changed_attributes = true;
}

} /* -- namespace Typograph */

} /* -- namespace OndraRT */
