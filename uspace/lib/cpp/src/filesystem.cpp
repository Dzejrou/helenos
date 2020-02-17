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
#include <__bits/functional/hash.hpp>

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
        if (p.is_absolute() ||
            (p.has_root_name() && p.root_name() != root_name()))
            return (*this = p);

        path_.append("/");
        path_.append(p.path_);

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
        return relative_path().empty() ? path{} : *--end();
    }

    path path::stem() const
    {
        auto res = filename();
        if (res.empty())
            return res;

        auto last_dot = res.path_.rfind('.');
        if (last_dot == string_type::npos)
            return res; // No dot in the path.

        if (last_dot == 0U || res.path_[last_dot - 1] == preferred_separator)
            return res; // Last dot is the start of a filename.
        if (res.path_[last_dot - 1] == '.')
            return res; // Double dot filename.
        res.path_.resize(last_dot);

        return res;
    }

    path path::extension() const
    {
        // TODO: make generic way to get dot and slash (for root, not sep)
        auto fname = filename();
        if (fname.empty())
            return path{};

        auto last_dot = fname.path_.rfind('.');
        auto npos = string_type::npos;

        if (last_dot == npos)
            return path{};
        if (last_dot == string_type::size_type{})
            return path{}; // Fname is current dir.
        if (last_dot == 1U && fname.path_[0] == '.')
            return path{}; // Fname is parent dir.
        return fname.path_.substr(last_dot, npos);
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
        auto relative = lexically_normal()
            .lexically_relative(base.lexically_normal());

        if (!relative.empty())
            return relative;
        else
            return *this;
    }

    path::iterator::iterator(const path& p, bool end)
        : idx_{}, size_{}, elements_{}
    {
        size_ = get_element_count_(p.path_);
        elements_ = split_path_to_elements_(p.path_, size_);

        /**
         * The iterator is bidirectional, so we need to
         * have the end() iterator to still be valid once
         * decremented.
         */
        if (end)
            idx_ = size_;
    }

    path::iterator::iterator(const path::iterator& it)
        : idx_{it.idx_}, size_{it.size_}, elements_{}
    {
        if (size_ > 0U)
        {
            elements_ = new path[size_];
            for (size_t i = 0U; i < size_; ++i)
                elements_[i] = it.elements_[i];
        }
    }

    path::iterator& path::iterator::operator=(const path::iterator& it)
    {
        if (elements_)
            delete[] elements_;

        idx_ = it.idx_;
        size_ = it.size_;
        if (size_ > 0U)
        {
            elements_ = new path[size_];
            for (size_t i = 0U; i < size_; ++i)
                elements_[i] = it.elements_[i];
        }

        return *this;
    }

    path::iterator::iterator(path::iterator&& it)
        : idx_{it.idx_}, size_{it.size_}, elements_{it.elements_}
    {
        it.idx_ = 0U;
        it.size_ = 0U;
        it.elements_ = nullptr;
    }

    path::iterator& path::iterator::operator=(path::iterator&& it)
    {
        if (elements_)
            delete[] elements_;
        idx_ = it.idx_;
        size_ = it.size_;
        elements_ = it.elements_;

        it.idx_ = 0U;
        it.size_ = 0U;
        it.elements_ = nullptr;

        return *this;
    }

    bool path::iterator::operator==(const path::iterator& it)
    {
        // 1) Default initialized iterators are equal.
        if (!elements_ && !it.elements_)
            return true;
        else if (!elements_ || !it.elements_)
            return false;

        // 2) Check the actual path.
        if (size_ == it.size_)
        {
            for (size_t i = 0U; i < size_; ++i)
            {
                if (elements_[i] != it.elements_[i])
                    return false;
            }
        }
        else
            return false;

        // 3) Check indices.
        return idx_ == it.idx_;
    }

    bool path::iterator::has_trailing_element_(const string_type& str)
    {
        if (str.empty())
            return false;
        if (str[0] != '/')
            return true;
        if (str[1] != '/' && str[str.size() - 1] != '/')
            return true;
        return false;
    }

    size_t path::iterator::get_element_count_(const string_type& str)
    {
        size_t size{};
        if (str.empty())
            return size;

        size_t element_start{};
        if (str[0] == '/')
        {
            ++element_start;
            ++size;
        }

        for (size_t i = element_start; i < str.size(); ++i)
        {
            if (str[i] == preferred_separator)
            {
                if (i != element_start)
                    ++size;
                element_start = i + 1; // Avoid duplicate separators.
            }
        }

        /**
         * This is for trailing filenames, i.e. those that
         * are not followed by a separator. It also covers
         * a trailing separator which the standard requires
         * to be added as an element.
         * The requirement for inequality with 1U is for
         * the case of path{'/'} as that is the only case
         * when there is no trailing part.
         */
        if (has_trailing_element_(str))
            ++size;

        return size;
    }

    path*
    path::iterator::split_path_to_elements_(const string_type& str, size_t size)
    {
        if (str.empty() || size == 0U)
            return nullptr;

        path* elements = new path[size];
        size_t idx{};

        size_t element_start{};
        if (str[0] == '/')
        {
            ++element_start;
            elements[idx++] = path{"/"};
        }

        for (size_t i = element_start; i < str.size(); ++i)
        {
            if (str[i] == preferred_separator)
            {
                if (i != element_start)
                {
                    auto count = i - element_start;
                    elements[idx++] = path{
                        str.substr(element_start, count)
                    };
                }
                element_start = i + 1;
            }
        }

        if (has_trailing_element_(str))
        {
            /**
             * The last separator as its own element
             * is required by the standard.
             */
            if (str[str.size() - 1] == preferred_separator)
                elements[idx] = path{"/"};
            else
            { // Last element of a path that does not end with separator.
                auto count = str.size() - element_start;
                elements[idx] = path{
                    str.substr(element_start, count)
                };
            }
        }

        return elements;
    }

    auto path::begin() const -> iterator
    {
        return iterator{*this, false};
    }

    auto path::end() const -> iterator
    {
        return iterator{*this, true};
    }

    void swap(path& lhs, path& rhs) noexcept
    {
        lhs.swap(rhs);
    }

    size_t hash_value(const path& p) noexcept
    {
        return hash<path::string_type>{}(p.path_);
    }

    bool operator==(const path& lhs, const path& rhs) noexcept
    {
        return !(lhs < rhs) && !(rhs < lhs);
    }
    bool operator!=(const path& lhs, const path& rhs) noexcept
    {
        return !(lhs == rhs);
    }

    bool operator<(const path& lhs, const path& rhs) noexcept
    {
        return lhs.compare(rhs) < 0;
    }

    bool operator<=(const path& lhs, const path& rhs) noexcept
    {
        return !(rhs < lhs);
    }

    bool operator>(const path& lhs, const path& rhs) noexcept
    {
        return rhs < lhs;
    }

    bool operator>=(const path& lhs, const path& rhs) noexcept
    {
        return !(lhs < rhs);
    }

    path operator/(const path& lhs, const path& rhs)
    {
        return path{lhs} /= rhs;
    }
}
