/*
 * Copyright (c) 2020 Jaroslav Jindrak
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * - The name of the author may not be used to endorse or promote products
 *   derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <__bits/io/fs/filesystem.hpp>
#include <__bits/utility/forward_move.hpp>

namespace std::filesystem
{
    path::path()
        : path_{}
    { /* DUMMY BODY */ }

    path::path(const path& p)
        : path_{p.path_}
    { /* DUMMY BODY */ }

    path::path(path&& p)
        : path_{move(p.path_)}
    { /* DUMMY BODY */ }

    path::path(string_type&& src, format fmt)
        : path_{move(src)}
    {
        LIBCPP_CONVERT_PATH(fmt);
    }

    path& path::operator=(const path& p)
    {
        if (this != &p)
            path_ = p.path_;

        return *this;
    }

    path& path::operator=(path&& p)
    {
        if (this != &p)
            swap(p);

        return *this;
    }

    path& path::operator=(string_type&& src)
    {
        path_ = move(src);

        return *this;
    }

    path& path::assign(string_type&& src)
    {
        return (*this = move(src));
    }

    path& path::operator/=(const path& p)
    {
        /* if (p.is_absolute() || */
        /*     (p.has_root_name() && p.root_name() != root_name())) */
        /*     return (*this = p); */

        // TODO:
        return *this;
    }

    path& path::operator+=(const path& p)
    {
        path_.append(p.native());

        return *this;
    }

    path& path::operator+=(const string_type& src)
    {
        path_.append(src);

        return *this;
    }

    path& path::operator+=(const value_type* src)
    {
        path_.append(src);

        return *this;
    }

    path& path::operator+=(value_type c)
    {
        path_.append(1U, c);

        return *this;
    }

    path& path::make_preferred()
    {
        // TODO:
        __unimplemented();

        return *this;
    }

    path& path::remove_filename()
    {
        // TODO:
        __unimplemented();

        return *this;
    }

    path& path::replace_filename(const path& replacement)
    {
        // TODO:
        __unimplemented();

        return *this;
    }

    path& path::replace_extension(const path& replacement)
    {
        // TODO:
        __unimplemented();

        return *this;
    }

    std::string path::string() const
    {
        return path_;
    }

    std::wstring path::wstring() const
    {
        __unimplemented();

        return {};
    }

    std::string path::generic_string() const
    {
        return path_;
    }

    std::wstring path::generic_wstring() const
    {
        __unimplemented();

        return {};
    }

    int path::compare(const path& p) const
    {
        return path_.compare(p.path_);
    }

    int path::compare(const string_type& str) const
    {
        return compare(path{str});
    }

    int path::compare(const value_type* str) const
    {
        return compare(path{str});
    }

    path path::root_name() const
    {
        /**
         * Note: HelenOS has empty root name, so we will
         *       return an empty path.
         */
        return path{};
    }

    path path::root_directory() const
    {
        /**
         * Note: HelenOS only has one root, so we only
         *       need to check it is included in the path
         *       and then return a new path with just it.
         */
        if (path_.size() > 1U && path_[0] == '/')
            return path{"/"};
        else
            return path{};
    }

    path path::root_path() const
    {
        /**
         * Note: HelenOS has no root name, otherwise
         *       this would be root_name() / root_directory().
         */
        return root_directory();
    }

    path path::relative_path() const
    {
        if (empty())
            return path{};

        if (path_[0] == '/')
            return path_.substr(1U);
        else
            return path_;
    }

    path path::parent_path() const
    {
        if (!has_relative_path())
            return *this;

        auto last_sep = path_.rfind(preferred_separator);
        if (last_sep == string_type::npos)
            return path{};
        else
            return path{path_.substr(0U, last_sep)};
    }

    path path::filename() const
    {
        /* return relative_path().empty() ? path{} : *--end(); */
        // TODO: need operator-- on path::iterator
        __unimplemented();

        return {};
    }

    path path::stem() const
    {
        // TODO:
        __unimplemented();

        return {};
    }

    path path::extension() const
    {
        // TODO:
        __unimplemented();

        return {};
    }

    bool path::has_root_name() const
    {
        return !root_name().empty();
    }

    bool path::has_root_directory() const
    {
        return !root_name().empty();
    }

    bool path::has_root_path() const
    {
        return !root_path().empty();
    }

    bool path::has_relative_path() const
    {
        return !relative_path().empty();
    }

    bool path::has_parent_path() const
    {
        return !parent_path().empty();
    }

    bool path::has_filename() const
    {
        return !filename().empty();
    }

    bool path::has_stem() const
    {
        return !stem().empty();
    }

    bool path::has_extension() const
    {
        return !extension().empty();
    }

    bool path::is_absolute() const
    {
        return path_.size() > 1U && path_[0] == '/';
    }

    bool path::is_relative() const
    {
        return !is_absolute();
    }

    path path::lexically_normal() const
    {
        // TODO:
        __unimplemented();

        return {};
    }

    path path::lexically_relative(const path& base) const
    {
        // TODO:
        __unimplemented();

        return {};
    }

    path path::lexically_proximate(const path& base) const
    {
        // TODO:
        __unimplemented();

        return {};
    }

    // TODO: iterator

    auto path::begin() const -> iterator
    {
        // TODO:
        __unimplemented();

        return {};
    }

    auto path::end() const -> iterator
    {
        // TODO:
        __unimplemented();

        return {};
    }
}
