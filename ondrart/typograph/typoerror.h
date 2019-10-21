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

#ifndef OndraRT__TYPOERROR_H_
#define OndraRT__TYPOERROR_H_

#include <string>

namespace OndraRT {

namespace Typograph {

class TypoError {
  public:
    explicit TypoError(
        const std::string& message_);
    TypoError(
        TypoError&&);
    ~TypoError();

    /* -- avoid copying */
    TypoError(
        const TypoError&) = delete;
    TypoError& operator =(
        const TypoError&) = delete;

  public:
    std::string message;
};

} /* -- namespace Typograph */

} /* -- namespace OndraRT */

#endif /* OndraRT__TYPOERROR_H_ */
