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

#ifndef OndraRT__TYPOGRAPHBLOCKHOLDER_H_
#define OndraRT__TYPOGRAPHBLOCKHOLDER_H_

#include <memory>
#include <vector>

namespace OndraRT {

namespace Typograph {

class TypographBlock;

/**
 * @brief A helper holder of the ownership of typograph blocks
 */
class TypographBlockHolder {
  public:
    /**
     * @brief Ctor
     */
    TypographBlockHolder();

    /**
     * @brief Dtor
     */
    ~TypographBlockHolder();

    /**
     * @brief Get the ownership of a block
     *
     * @param block_ the block
     * @return the block
     */
    TypographBlock* holdBlock(
        std::unique_ptr<TypographBlock>&& block_);

    /**
     * @brief Create new block
     *
     * @param args_ arguments of the block (perfectly forwarded into the
     *     constructor)
     * @return The block
     */
    template<typename Block_, typename... Args_>
    Block_* createBlock(
        Args_&&... args_) {
      return static_cast<Block_*>(holdBlock(
          std::unique_ptr<Block_>(new Block_(std::forward<Args_>(args_)...))));
    }

  private:
    std::vector<std::unique_ptr<TypographBlock>> blocks;
};

} /* -- namespace Typograph */

} /* -- namespace OndraRT */

#endif /* OndraRT__TYPOGRAPHBLOCKHOLDER_H_ */
