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

#ifndef OndraRT__GETOPT_H_
#define OndraRT__GETOPT_H_

#include <iosfwd>
#include <functional>
#include <string>

namespace OndraRT {

namespace Usage {

/**
 * @brief Specification of option occurrences
 *
 * examples:
 *   - {0,1} optional option
 *   - {1,1} mandatory option
 *   - {1, -1} mandatory repeatable option
 */
struct Presence {
    int min;   /**< minimal count of option occurrences */
    int max;   /**< maximal count of option occurrences, -1 == infinity */
};

/**
 * @brief presence of an option argument
 */
enum class PresenceArg {
    OPTIONAL,  /**< optional argument */
    EMPTY,     /**< mandatory but it can be empty */
    NOT_EMPTY, /**< mandatory but it cannot be empty */
};

/**
 * @brief A facility parsing command line options
 *
 * This is a parser of command line options. It's behavior is similar
 * to standard getopt() function but it can do more: mainly it formats
 * the help message too.
 */
class Usage {
  public:

    /**
     * @brief Ctor
     *
     * @param argc_ number of command line parameters
     * @param argv_ command line parameters
     */
    explicit Usage(
        int argc_,
        char* argv_[]);

    /**
     * @brief Ctor
     *
     * @param argc_ number of command line parameters
     * @param argv_ command line parameters
     * @param name_ Name of the binary (shown in the help message)
     * @param brief_ Brief description of the binary
     */
    explicit Usage(
        int argc_,
        char* argv_[],
        const std::string& name_,
        const std::string& brief_);

    /**
     * @brief Ctor
     *
     * @param argc_ number of command line parameters
     * @param argv_ command line parameters
     * @param name_ Name of the binary (shown in the help message)
     * @param brief_ Brief description of the binary
     * @param extra_args_ A text shown after command line options (other
     *     positional parameters)
     */
    explicit Usage(
        int argc_,
        char* argv_[],
        const std::string& name_,
        const std::string& brief_,
        const std::string& extra_args_);

    /**
     * @brief Dtor
     */
    ~Usage();

    /* -- avoid copying */
    Usage(
        const Usage&) = delete;
    Usage& operator =(
        const Usage&) = delete;

    /**
     * @brief Set shown name of the binary
     *
     * @param name_ The name. It can contain placeholder $n which is replaced
     *     by the n-th argument. Likely the $0 will be most usefull in this
     *     context.
     */
    void setName(
        const std::string& name_);

    /**
     * @brief Set brief description of the binary
     *
     * @param brief_ The brief description. It can contain $n placeholders
     *     and any formatting sequences supported by the OndraRT::Typograph.
     */
    void setBrief(
        const std::string& brief_);

    /**
     * @brief Set extra arguments shown after the command line options
     *
     * @param extra_args_ The arguments.  It can contain $n placeholders
     *     and any formatting sequences supported by the OndraRT::Typograph.
     */
    void setExtraArgs(
        const std::string& extra_args_);

    /**
     * @brief Open a section
     *
     * This opens a section -> all nested items will be indented.
     *
     * @param title_ Title of the section
     */
    void openSection(
        const std::string& title_);

    /**
     * @brief Add new command line option without argument
     *
     * @param presence_ Presence of the option (mandatory/optional)
     * @param short_ The short option. It can be zero, if there is no short
     *     version
     * @param long_ The long option. It can be empty, if there is no long
     *     version
     * @param help_ Help text associated with the option.
     * @param handler_ A handler invoked if the option is parsed. The argument
     *     is the name of the option.
     */
    void addOption(
        Presence presence_,
        char short_,
        const std::string& long_,
        const std::string& help_,
        std::function<void(const std::string&)> handler_);

    /**
     * @brief Add new command line option with an argument
     *
     * @param presence_ Presence of the option (mandatory/optional)
     * @param short_ The short option. It can be zero, if there is no short
     *     version
     * @param long_ The long option. It can be empty, if there is no long
     *     version
     * @param arg_presence_ Presence of the argument (mandatory/optional)
     * @param arg_name_ Name of the argument (shown in the help)
     * @param help_ Help text associated with the option
     * @param handler_ A handler invoked if the option is parsed. First
     *     argument if the name of the option. The second argument is the
     *     value of the option's argument. If it's null, the argument is not
     *     present.
     */
    void addOptionArg(
        Presence presence_,
        char short_,
        const std::string& long_,
        PresenceArg arg_presence_,
        const std::string& arg_name_,
        const std::string& help_,
        std::function<void(const std::string&, const std::string*)> handler_);

    /**
     * @brief Add free text
     *
     * @param text_ The text. It can contain any formatting sequence of the
     *     OndraRT::Typograph, $n placeholders and empty lines separating
     *     paragraphs.
     */
    void addText(
        const std::string& text_);

    /**
     * @brief Add
     * @param to_explain_
     * @param explanation_
     */
    void addExplanation(
        const std::string& to_explain_,
        const std::string& explanation_);

    /**
     * @brief Close currently opened section
     */
    void closeSection();

    /**
     * @brief Print usage into the standard output
     */
    void printUsage();

    /**
     * @brief Print usage into a stream
     *
     * @param os_ The stream
     * @param width_ Width of the output in characters. If the the value
     *     is negative, the width is detected or the default (80 characters)
     *     is used.
     * @param terminal_ True if the stream should be handled as terminal
     *     (the control sequences will be printed)
     */
    void printUsage(
        std::ostream& os_,
        int width_,
        bool terminal_);

  private:
    struct Impl;
    Impl* pimpl;
};

} /* -- namespace Getopt */

} /* -- namespace OndraRT */

#endif /* OndraRT__GETOPT_H_ */
