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

#ifndef OndraRT__TYPOGRAPHSTATE_H_
#define OndraRT__TYPOGRAPHSTATE_H_

#include <vector>

#include "linedriver.h"

namespace OndraRT {

namespace Typograph {

/**
 * @brief Current state of text attributes
 */
class TypographState {
  public:
    /**
     * @brief Ctor
     */
    explicit TypographState();

    /**
     * @brief Ctor
     *
     * @param font_style_ Font style
     * @param font_weight Font weight
     * @param foreground_ Foreground color
     * @param background_ Background color
     */
    explicit TypographState(
        LineDriver::FontStyle font_style_,
        LineDriver::FontWeight font_weight_,
        LineDriver::Color foreground_,
        LineDriver::Color background_);

    /**
     * @brief Copy ctor
     */
    explicit TypographState(
        const TypographState& other_);

    /**
     * @brief Dtor
     */
    ~TypographState();

    /**
     * @brief Swap contents
     */
    void swap(
        TypographState& other_) noexcept;

    /**
     * @brief Copy assignment
     */
    TypographState& operator =(
        const TypographState& other_);

  private:
    LineDriver::FontStyle font_style;
    LineDriver::FontWeight font_weight;
    LineDriver::Color foreground;
    LineDriver::Color background;
    friend class TypographStateScope;
};

/**
 * @brief Scoped typograph state
 */
class TypographStateScope {
  public:
    /**
     * @brief Ctor
     *
     * @param driver_ Used line driver
     * @param origin_ Origin (parent) state
     * @param scope_ The scoped (mine) state
     */
    explicit TypographStateScope(
        LineDriver* driver_,
        const TypographState* origin_,
        TypographState* scope_);
    ~TypographStateScope();

    /* -- avoid copying */
    TypographStateScope(
        const TypographStateScope&) = delete;
    TypographStateScope& operator =(
        const TypographStateScope&) = delete;

    /**
     * @brief Get merged typograph state
     */
    const TypographState& getState() const noexcept;

    /**
     * @brief Set font style
     */
    void setFontStyle(
        LineDriver::FontStyle style_);

    /**
     * @brief Set font weight
     */
    void setFontWeight(
        LineDriver::FontWeight weight_);

    /**
     * @brief Change current foreground color
     */
    void setForeground(
        LineDriver::Color color_);

    /**
     * @brief Change current background color
     */
    void setBackground(
        LineDriver::Color color_);

  private:
    LineDriver* driver;
    const TypographState* origin;
    TypographState* scope;
    TypographState merged;
};

} /* -- namespace Typograph */

} /* -- namespace OndraRT */

#endif /* OndraRT__TYPOGRAPHSTATE_H_ */
