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

#ifndef OndraRT__TYPOGRAPH_H_
#define OndraRT__TYPOGRAPH_H_

namespace OndraRT {

namespace Typograph {

class LineDriver;
class TypographBlock;

/**
 * @brief A typograph object
 *
 * The typograph object is responsible to format block of texts to a line
 * driver (a text line oriented device, usually a terminal).
 *
 * The typograph object is useful for formatting of command line helps.
 */
class Typograph {
  public:
    /**
     * @brief Ctor
     *
     * @param driver_ A line driver. The ownership is not taken.
     * @param width_ Width of the line device
     */
    explicit Typograph(
        LineDriver* driver_,
        int width_);

    /**
     * @brief Dtor
     */
    ~Typograph();

    /* -- avoid copying */
    Typograph(
        const Typograph&) = delete;
    Typograph& operator =(
        const Typograph&) = delete;

    /**
     * @brief Write a text block
     *
     * @param block_ The block.
     */
    void writeBlock(
        TypographBlock& block_);

    /**
     * @brief Write empty line
     */
    void writeEmptyLine();

  private:
    LineDriver* driver;
    int width;
};

} /* -- namespace Typograph */

} /* -- namespace OndraRT */

#endif /* OndraRT__TYPOGRAPH_H_ */
