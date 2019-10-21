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

#include "usage.h"

#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

#include "linedriver.h"
#include "linedriverpre.h"
#include "typograph.h"
#include "typographblock.h"
#include "typographblockattrs.h"
#include "typographblockbox.h"
#include "typographblockcols.h"
#include "typographblockholder.h"
#include "typographblockpar.h"
#include "typographblocktext.h"

namespace OndraRT {

namespace Usage {

namespace T = Typograph;

namespace {

constexpr const int INDENT_LEVEL(2);

/**
 * @brief Usage context
 */
class UsageContext {
  public:
    explicit UsageContext(
        int width_,
        int max_short_,
        int max_long_);
    ~UsageContext();

    /* -- avoid copying */
    UsageContext(
        const UsageContext&) = delete;
    UsageContext& operator =(
        const UsageContext&) = delete;

    void incIndent();
    void decIndent();
    std::tuple<int, int, int> getOptionColumns() const;
    int getIndent() const;

  private:
    int width;
    int indent;
    int max_short;
    int max_long;
};

UsageContext::UsageContext(
    int width_,
    int max_short_,
    int max_long_) :
  width(width_),
  indent(0),
  max_short(max_short_),
  max_long(max_long_) {

}

UsageContext::~UsageContext() {

}

void UsageContext::incIndent() {
  width -= INDENT_LEVEL;
  ++indent;
}

void UsageContext::decIndent() {
  width += INDENT_LEVEL;
  --indent;
}

std::tuple<int, int, int> UsageContext::getOptionColumns() const {
  int inter_columns_(0);
  if (max_short > 0)
    ++inter_columns_;
  if (max_long > 0)
    ++inter_columns_;
  return std::tuple<int, int, int>(
      max_short, max_long, width - max_short - max_long - inter_columns_);
}

int UsageContext::getIndent() const {
  return indent * INDENT_LEVEL;
}

class UsageRecord {
  public:
    UsageRecord() = default;
    virtual ~UsageRecord() = default;

    /* -- avoid copying */
    UsageRecord(
        const UsageRecord&) = delete;
    UsageRecord& operator =(
        const UsageRecord&) = delete;

    virtual T::TypographBlock* printRecord(
        UsageContext& context_,
        T::TypographBlockHolder& holder_) const = 0;
};

class Section : public UsageRecord {
  public:
    explicit Section(
        const std::string& title_);
    virtual ~Section();

    /* -- avoid copying */
    Section(
        const Section&) = delete;
    Section& operator =(
        const Section&) = delete;

    virtual T::TypographBlock* printRecord(
        UsageContext& context_,
        T::TypographBlockHolder& holder_) const override;

  private:
    std::string title;
};

Section::Section(
    const std::string& title_) :
  title(title_) {

}

Section::~Section() {

}

T::TypographBlock* Section::printRecord(
    UsageContext& context_,
    T::TypographBlockHolder& holder_) const {
  /* -- create the formatting boxes */
  auto* text_(holder_.createBlock<T::TypographBlockText>(title));
  auto* attrs_(holder_.createBlock<T::TypographBlockAttrs>(
      text_,
      T::LineDriver::FS_DEFAULT,
      T::LineDriver::FW_BOLD,
      T::LineDriver::C_DEFAULT,
      T::LineDriver::C_DEFAULT));
  auto* box_(holder_.createBlock<T::TypographBlockBox>(attrs_, 0, 1, 0, 0));

  /* -- change indentantion */
  context_.incIndent();

  return box_;
}

class Option : public UsageRecord {
  public:
    explicit Option(
        Presence presence_,
        char short_,
        const std::string& long_,
        const std::string& help_);
    explicit Option(
        Presence presence_,
        char short_,
        const std::string& long_,
        PresenceArg arg_presence_,
        const std::string& arg_name_,
        const std::string& help_);
    virtual ~Option();

    /* -- avoid copying */
    Option(
        const Option&) = delete;
    Option& operator =(
        const Option&) = delete;

    virtual T::TypographBlock* printRecord(
        UsageContext& context_,
        T::TypographBlockHolder& holder_) const override;

  private:
    Presence presence;
    char short_opt;
    const std::string long_opt;
    bool argument;
    PresenceArg arg_presence;
    std::string arg_name;
    std::string help;
};

Option::Option(
    Presence presence_,
    char short_,
    const std::string& long_,
    const std::string& help_) :
  presence(presence_),
  short_opt(short_),
  long_opt(long_),
  argument(false),
  arg_presence(),
  arg_name(),
  help(help_) {

}

Option::Option(
    Presence presence_,
    char short_,
    const std::string& long_,
    PresenceArg arg_presence_,
    const std::string& arg_name_,
    const std::string& help_) :
  presence(presence_),
  short_opt(short_),
  long_opt(long_),
  argument(true),
  arg_presence(arg_presence_),
  arg_name(arg_name_),
  help(help_) {

}

Option::~Option() {

}

T::TypographBlock* Option::printRecord(
    UsageContext& context_,
    T::TypographBlockHolder& holder_) const {
  std::vector<T::TypographBlockCols::Column> cols_;
  auto col_widths_(context_.getOptionColumns());

  /* -- short argument */
  if (std::get<0>(col_widths_) > 0) {
    std::ostringstream oss_;
    if (short_opt != 0) {
      oss_ << '-' << short_opt;
      if (argument)
        oss_ << ' ' << arg_name;
    }
    auto* text_(holder_.createBlock<T::TypographBlockText>(oss_.str()));
    auto* attrs_(holder_.createBlock<T::TypographBlockAttrs>(
        text_,
        T::LineDriver::FS_DEFAULT,
        T::LineDriver::FW_BOLD,
        T::LineDriver::C_DEFAULT,
        T::LineDriver::C_DEFAULT));
    auto* box_(holder_.createBlock<T::TypographBlockBox>(attrs_, 0, 0, 1, 0));
    cols_.push_back({box_, std::get<0>(col_widths_)});
  }

  /* -- long argument */
  if (std::get<1>(col_widths_) > 0) {
    std::ostringstream oss_;
    if (!long_opt.empty()) {
      oss_ << "--" << long_opt;
      if (argument) {
        oss_ << '=';
        if (arg_presence == PresenceArg::OPTIONAL)
          oss_ << '[' << arg_name << ']';
        else
          oss_ << arg_name;
      }
    }
    auto* text_(holder_.createBlock<T::TypographBlockText>(oss_.str()));
    auto* attrs_(holder_.createBlock<T::TypographBlockAttrs>(
        text_,
        T::LineDriver::FS_DEFAULT,
        T::LineDriver::FW_BOLD,
        T::LineDriver::C_DEFAULT,
        T::LineDriver::C_DEFAULT));
    auto* box_(holder_.createBlock<T::TypographBlockBox>(attrs_, 0, 0, 1, 0));
    cols_.push_back({box_, std::get<1>(col_widths_)});
  }

  /* -- help text */
  auto* help_(holder_.createBlock<T::TypographBlockText>(help));
  cols_.push_back({help_, std::get<2>(col_widths_)});

  return holder_.createBlock<T::TypographBlockCols>(
      cols_.data(), cols_.size());
}

class CloseSection : public UsageRecord {
  public:
    CloseSection();
    virtual ~CloseSection();

    /* -- avoid copying */
    CloseSection(
        const CloseSection&) = delete;
    CloseSection& operator =(
        const CloseSection&) = delete;

    virtual T::TypographBlock* printRecord(
        UsageContext& context_,
        T::TypographBlockHolder& holder_) const override;
};

CloseSection::CloseSection() {

}

CloseSection::~CloseSection() {

}

T::TypographBlock* CloseSection::printRecord(
    UsageContext& context_,
    T::TypographBlockHolder& holder_) const {
  context_.decIndent();
  return nullptr;
}

} /* -- namespace */

struct Usage::Impl {
    int argc;
    char** argv;

    std::string name;
    std::string brief;
    std::string extra_args;

    /* -- usage records */
    int max_short;
    int max_long;
    typedef std::vector<std::unique_ptr<UsageRecord>> UsageRecords;
    UsageRecords usage;

    /* -- avoid copying */
    Impl(
        const Impl&) = delete;
    Impl& operator =(
        const Impl&) = delete;

    explicit Impl(
        int argc_,
        char* argv_[],
        const std::string& name_,
        const std::string& brief_,
        const std::string& extra_args_);
    ~Impl();
};

Usage::Impl::Impl(
    int argc_,
    char* argv_[],
    const std::string& name_,
    const std::string& brief_,
    const std::string& extra_args_) :
  argc(argc_),
  argv(argv_),
  name(name_),
  brief(brief_),
  extra_args(extra_args_),
  max_short(0),
  max_long(0),
  usage() {

}

Usage::Impl::~Impl() {

}

Usage::Usage(
    int argc_,
    char* argv_[]) :
  pimpl(new Impl(argc_, argv_, "$0", "", "")) {

}

Usage::Usage(
    int argc_,
    char* argv_[],
    const std::string& name_,
    const std::string& brief_) :
  pimpl(new Impl(argc_, argv_, name_, brief_, "")) {

}

Usage::Usage(
    int argc_,
    char* argv_[],
    const std::string& name_,
    const std::string& brief_,
    const std::string& extra_args_) :
  pimpl(new Impl(argc_, argv_, name_, brief_, extra_args_)) {

}

Usage::~Usage() {
  delete pimpl;
  pimpl = nullptr;
}

void Usage::setName(
    const std::string& name_) {
  pimpl->name = name_;
}

void Usage::setBrief(
    const std::string& brief_) {
  pimpl->brief = brief_;
}

void Usage::setExtraArgs(
    const std::string& extra_args_) {
  pimpl->extra_args = extra_args_;
}

void Usage::openSection(
    const std::string& title_) {
  pimpl->usage.emplace_back(new Section(title_));
}

void Usage::addOption(
    Presence presence_,
    char short_,
    const std::string& long_,
    const std::string& help_) {
  /* -- maximal lengths of the options help descriptions */
  if (short_ != 0 && pimpl->max_short < 2) {
    pimpl->max_short = 2;  /* -- '-' + short char */
  }
  if (!long_.empty() && pimpl->max_long < long_.length() + 2) {
    pimpl->max_long = long_.length() + 2; /* -- '--' long */
  }

  /* -- create the usage record */
  pimpl->usage.emplace_back(new Option(presence_, short_, long_, help_));
}

void Usage::addOptionArg(
    Presence presence_,
    char short_,
    const std::string& long_,
    PresenceArg arg_presence_,
    const std::string& arg_name_,
    const std::string& help_) {
  /* -- maximal lengths of the options help descriptions */
  int name_len_(arg_name_.length());
  if (arg_presence_ == PresenceArg::OPTIONAL)
    name_len_ += 2; /* -- [ and ] wrapping the name */
  if (short_ != 0 && pimpl->max_short < name_len_ + 3) {
    pimpl->max_short = name_len_ + 3;  /* -- '-' + short char + space + name */
  }
  if (!long_.empty() && pimpl->max_long < long_.length() + 3 + name_len_) {
    pimpl->max_long = long_.length() + 3 + name_len_; /* -- '--' long '=' name */
  }

  /* -- create the usage record */
  pimpl->usage.emplace_back(new Option(
      presence_, short_, long_, arg_presence_, arg_name_, help_));
}

void Usage::addText(
    const std::string& text_) {

}

void Usage::addExplanation(
    const std::string& to_explain_,
    const std::string& explanation_) {

}

void Usage::closeSection() {
  pimpl->usage.emplace_back(new CloseSection());
}

void Usage::printUsage() {
  printUsage(std::cout, -1, false);
}

void Usage::printUsage(
    std::ostream& os_,
    int width_,
    bool terminal_) {
  /* -- TODO: detect width of the terminal */
  if(width_ < 0)
    width_ = 80;

  /* -- construct the typograph */
  os_ << "<html><body><pre>" << std::endl;
  T::LineDriverPre driver_(&os_);
  T::Typograph typograph_(&driver_, width_);

  /* -- print usage */
  UsageContext context_(width_, pimpl->max_short, pimpl->max_long);
  for(const auto& record_ : pimpl->usage) {
    T::TypographBlockHolder holder_;

    /* -- get left padding for indentation before the record changes
     *    the context. */
    int left_padding_(context_.getIndent());
    auto* block_(record_->printRecord(context_, holder_));
    if(block_ != nullptr) {
      T::TypographBlockBox box_(block_, 0);
      box_.setPadding(left_padding_, 0, 0, 0);
      typograph_.writeBlock(box_);
    }
  }
  os_ << "</pre></body></html>" << std::endl;
}

} /* -- namespace Getopt */

} /* -- namespace OndraRT */
