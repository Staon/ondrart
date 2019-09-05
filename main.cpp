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

#include <iostream>
#include <string>

#include "getopt.h"
#include "linedriverios.h"
#include "linedriverpre.h"
#include "typograph.h"
#include "typographblockattrs.h"
#include "typographblockbox.h"
#include "typographblockcols.h"
#include "typographblockpar.h"
#include "typographblockseq.h"
#include "typographblocktext.h"

namespace T = ::OndraRT::Typograph;
namespace G = ::OndraRT::Getopt;

int main(
    int argc_,
    char* argv_[]) {
//  std::cout << "<html><body><pre>" << std::endl;
//
//  T::LineDriverPre driver_(&std::cout);
//  T::LineDriverIos driver2_(&std::cout, T::LineDriverIos::SYNC);
//  T::Typograph typo_(&driver_, 80);
//
//  T::TypographBlockText block1_(
//"#bg:blue#Lorem *ipsum* **dolor** sit amet, consectetuer adipiscing elit. Nulla est. Lorem "
//"ipsum dolor #fg:red#sit amet, consectetuer adipiscing elit. Ut enim ad minim veniam, "
//"quis nos*trud exe**rcitation* ullamco** laboris nisi ut aliquip ex ea commodo "
//"consequat. Integer pellentesque quam vel velit. Etiam dui sem, fermentum "
//"vitae, sa#fg:cyan#gitt#fg#is id, malesuada in, quam.#bg# Itaque earum rerum hic tenetur a "
//"sapiente delectus, ut aut reiciendis voluptatibus maiores alias consequatur "
//"aut perferendis doloribus asperiores repellat. Ut tempus purus at lorem. "
//"Aliquam erat volutpat. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos hymenaeos. Vivamus porttitor turpis ac leo. Sed vel lectus. Donec odio tempus molestie, porttitor ut, iaculis quis, sem. Nunc dapibus tortor vel mi dapibus sollicitudin. "
//"Integer pellentesque quam vel velit. Donec ipsum massa, ullamcorper in, auctor et, scelerisque sed, est. Praesent in mauris eu tortor porttitor accumsan. Nulla est. Fusce wisi. Mauris elementum mauris vitae tortor. Suspendisse sagittis ultrices augue. Aliquam erat volutpat. Quisque tincidunt scelerisque libero. Proin in tellus sit amet nibh dignissim sagittis. In dapibus augue non sapien. Phasellus enim erat, vestibulum vel, aliquam a, posuere eu, velit. Maecenas aliquet accumsan leo. "
//"Aliquam ante. Mauris tincidunt sem sed arcu. Integer rutrum, orci vestibulum ullamcorper ultricies, lacus quam ultricies odio, vitae placerat pede sem sit amet enim. Sed elit dui, pellentesque a, faucibus vel, interdum nec, diam. Nullam sit amet magna in magna gravida vehicula. Etiam dui sem, fermentum vitae, sagittis id, malesuada in, quam. Integer vulputate sem a nibh rutrum consequat. Pellentesque sapien. Quisque porta. Fusce consectetuer risus a nunc. Vivamus ac leo pretium faucibus. Praesent id justo in neque elementum ultrices. Nullam sit amet magna in magna gravida vehicula. Nam sed tellus id magna elementum tincidunt. Nullam dapibus fermentum ipsum. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum. Nulla turpis magna, cursus sit amet, suscipit a, interdum id, felis. ");
//  T::TypographBlockPar par1_(&block1_, 2, 0);
//  T::TypographBlockBox box1_(&par1_, 0, 0, 0, 0);
//  box1_.setPadding(0, 0, 0, 0);
//  T::TypographBlockAttrs attrs1_(
//      &box1_,
//      T::LineDriver::FS_DEFAULT,
//      T::LineDriver::FW_DEFAULT,
//      T::LineDriver::C_DEFAULT,
//      T::LineDriver::C_CYAN);
//
//  T::TypographBlockText block2_(
//"Fusce tellus. In laoreet, magna id viverra tincidunt, sem odio bibendum justo, "
//"vel imperdiet sapien wisi sed libero. Pellentesque ipsum. Phasellus et lorem "
//"id felis nonummy placerat. Donec ipsum massa, ullamcorper in, auctor et, "
//"scelerisque sed, est. Phasellus rhoncus. In laoreet, magna id viverra "
//"tincidunt, sem odio bibendum justo, vel imperdiet sapien wisi sed libero. "
//"Mauris elementum mauris vitae tortor. Aliquam erat volutpat. Nullam feugiat, "
//"turpis at pulvinar vulputate, erat libero tristique tellus, nec bibendum odio "
//"risus sit amet ante. Etiam ligula pede, sagittis quis, interdum ultricies, "
//"scelerisque eu. Nam quis nulla.");
//  T::TypographBlockPar par2_(&block2_, 0, 2);
//  T::TypographBlockBox box2_(&par2_, 0, 0, 0, 0);
//
//  T::TypographBlock* aseq1[] = {&attrs1_, &box2_};
//  T::TypographBlockSeq seq1_(aseq1, 2);
//
//  T::TypographBlockText block3_(
//"Nulla pulvinar eleifend sem. Etiam quis quam. Curabitur bibendum justo non orci. Integer tempor. Proin in tellus sit amet nibh dignissim sagittis. Integer rutrum, orci vestibulum ullamcorper ultricies, lacus quam ultricies odio, vitae placerat pede sem sit amet enim. Proin mattis lacinia justo. Suspendisse sagittis ultrices augue. Nunc dapibus tortor vel mi dapibus sollicitudin. Vivamus porttitor turpis ac leo. Nulla accumsan, elit sit amet varius semper, nulla mauris mollis quam, tempor suscipit diam nulla vel leo. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos hymenaeos. Aenean id metus id velit ullamcorper pulvinar. Aenean placerat. Aliquam erat volutpat. Praesent in mauris eu tortor porttitor accumsan. Cras pede libero, dapibus nec, pretium sit amet, tempor quis.");
//  T::TypographBlockPar par3_(&block3_, 4, 0);
//  T::TypographBlockBox box3_(&par3_, 2, 0, 2, 0);
//  T::TypographBlockBox box4_(&box3_, 0);
//  box4_.setPadding(5);
//
//  T::TypographBlockCols::Column cols_[2] = {
//      {&seq1_, -1},
//      {&box4_, -1},
//  };
//  T::TypographBlockCols tcols_(cols_, 2);
//  T::TypographBlockAttrs attrs2_(
//      &tcols_,
//      T::LineDriver::FS_DEFAULT,
//      T::LineDriver::FW_DEFAULT,
//      T::LineDriver::C_DEFAULT,
//      T::LineDriver::C_YELLOW);
//
//  typo_.writeBlock(attrs2_);
//
//  std::cout << "</pre></body></html>" << std::endl;

  G::Getopt getopt_(argc_, argv_);
  getopt_.openSection("Command line options");
  getopt_.addOption(
      {0, 1}, 'h', "help",
      "Print help message. The help message must be long enough to be wrapped.",
      [](const std::string& opt_){});
  getopt_.addOption(
      {1, 1}, 'c', "",
      "Short option mandatory",
      [](const std::string& opt_){});
  getopt_.addOption(
      {1, 1}, 0, "long1",
      "Long option mandatory",
      [](const std::string& opt_){});
  getopt_.addOptionArg(
      {1, 1}, 's', "argopt", G::PresenceArg::NOT_EMPTY, "argument",
      "This is a mandatory *option* with a **mandatory** argument.",
      [](const std::string&, const std::string*){});
  getopt_.addOptionArg(
      {1, 1}, 'x', "argopt-e", G::PresenceArg::EMPTY, "argument",
      "This is a mandatory *option* with a possibly **empty** argument.",
      [](const std::string&, const std::string*){});
  getopt_.addOptionArg(
      {1, 1}, 0, "argopt2", G::PresenceArg::OPTIONAL, "argument",
      "This is a mandatory *option* with an **optional** #fg:red#argument#fg#.",
      [](const std::string&, const std::string*){});
  getopt_.closeSection();

  getopt_.printUsage();
}
