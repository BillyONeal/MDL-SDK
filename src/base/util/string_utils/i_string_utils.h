/***************************************************************************************************
 * Copyright (c) 2010-2018, NVIDIA CORPORATION. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  * Neither the name of NVIDIA CORPORATION nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 **************************************************************************************************/

/// \file
/// \brief Collection of utilities for strings.

#ifndef BASE_UTIL_STRING_UTILS_I_STRING_UTILS_H
#define BASE_UTIL_STRING_UTILS_I_STRING_UTILS_H

#include <string>
#include <vector>

namespace MI {
namespace STRING {

/// \name Stripping
/// Stripping utilities.
//@{
/// Strip given leading and trailing characters. If no characters are given
/// then all valid whitespace characters will be taken instead.
/// \param str given input
/// \param sep characters to be stripped
/// \return stripped input
MISTD::string strip(
    const MISTD::string& str,
    const MISTD::string& sep=MISTD::string());

/// Strip given leading characters. If no characters are given
/// then all valid whitespace characters will be taken instead.
/// \param str given input
/// \param sep characters to be stripped
/// \return stripped input
MISTD::string lstrip(
    const MISTD::string& str,
    const MISTD::string& sep=MISTD::string());

/// Strip given trailing characters. If no characters are given
/// then all valid whitespace characters will be taken instead.
/// \param str given input
/// \param sep characters to be stripped
/// \return stripped input
MISTD::string rstrip(
    const MISTD::string& str,
    const MISTD::string& sep=MISTD::string());
//@}


/// \name Conversions
/// Conversion utilities.
//@{
/// Convert the given string \p input to a string where all characters are lowercase.
/// \param[in,out] input the input string
void to_lower(
    MISTD::string& input);

/// Convert the given string \p input to a string where all characters are uppercase.
/// \param[in,out] input the input string
void to_upper(
    MISTD::string& input);

/// Convert the given string \p input to a string where all characters are lowercase.
/// \param input the input string
/// \return converted string
MISTD::string to_lower(
    const MISTD::string& input);

/// Convert the given string \p input to a string where all characters are uppercase.
/// \param input the input string
/// \return converted string
MISTD::string to_upper(
    const MISTD::string& input);
//@}

/// Convert the given char input of UTF-8 format into a wchar.
MISTD::wstring utf8_to_wchar(
    const char* str);
#ifdef WIN_NT
/// Convert the given wchar string input into a multibyte char string output.
MISTD::string wchar_to_mbs(
    const wchar_t* str);

/// Converts a wchar_t * string into an utf8 encoded string.
MISTD::string wchar_to_utf8(
    const wchar_t* str);

#endif

/// Parse and get a token list.
/// A convenient function for getting a token list.
///
/// Example:
/// \code
///   std::vector<std::string> token_list;
///   Tokenizer::parse("A Non-Manifold,Mesh", " ,", token_list);
/// \endcode
/// gives
///   token_list[0] == "A";
///   token_list[1] == "Non-Manifold";
///   token_list[2] == "Mesh";
///
/// Notice: If the last entry is empty, it does not count.
///
/// For example, tokenize "hello," with "," gives only one token {
/// "hello" } instead of two tokens {"hello", ""}. But, tokenize
/// "hello,,world" with "," gives three tokens { "hello", "",
/// "world" }.
///
/// \param[in] source_str the source string
/// \param[in] separators the separators
/// \param[in,out] token_list the tokens will end up here
void split(
    const MISTD::string& source_str,
    const MISTD::string& separators,
    MISTD::vector<MISTD::string>& token_list);

/// Case insensitive string comparison which behaves like strcasecmp and strncasecmp
/// \param s1 string 1
/// \param s2 string 2
/// \return an integer less than, equal to, or greater than zero if s1 is found,
///         respectively, to be less than, to match, or be greater than s2.
int compare_case_insensitive(
    const char* s1,
    const char* s2);


/// Just like compare_case_insensitive() but only compares the n first characters
/// \param s1 string 1
/// \param s2 string 2
/// \param n  length to compare
/// \return an integer less than, equal to, or greater than zero if s1 (or the
///         first n bytes thereof) is found, respectively, to be less than,
///         to match, or be greater than s2.
int compare_case_insensitive(
    const char* s1,
    const char* s2,
    size_t n);
    
}
}

#endif