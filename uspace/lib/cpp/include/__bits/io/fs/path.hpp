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

#ifndef LIBCPP_BITS_IO_FS_PATH
#define LIBCPP_BITS_IO_FS_PATH

#include <cstdlib>
#include <iosfwd>
#include <iterator>
#include <locale>
#include <string>

// TODO: explain these, path conversion might not be needed
//       as for us native == generic (POSIX paths)
//       also: remove any use of native <-> generic conversions
//       as helenos does need it
#define LIBCPP_CONVERT_ENC(str, loc) str
#define LIBCPP_CONVERT_ENC_RANGE(first, last, loc) string_type{first, last}

/**
 * TODO: Functions taking template parameters named Source
 *       shall not participate in overload resolution unless
 *       either:
 *       1) Source is a specialization of basic_string or basic_string_view, or
 *       2) the qualified-id iterator_traits<decay_t<Source>>::value_type is
 *          valid and denotes a possibly const encoded character type.
 */
namespace std::filesystem
{
    /**
     * [n4659] 30.10.8, paths:
     */

    class path
    {
        public:
            using value_type = char;
            using string_type = basic_string<value_type>;

            static constexpr value_type preferred_separator = '/';

            /**
             * [n4659] 30.10.10.1, enumeration format:
             * Note: These are irrelevant for us as for HelenOS
             *       the preferred format is the same as the native
             *       format.
             */

            enum format
            {
                native_format,
                generic_format,
                auto_format
            };

            /**
             * [n4659] 30.10.8.4.1, constructors and destructor:
             */

            path() noexcept;
            path(const path& p);
            path(path&& p) noexcept;
            path(string_type&& src, format fmt = auto_format);

            template<class Source>
            path(const Source& src, format fmt = auto_format)
                : path_{src}
            { /* DUMMY BODY */ }

            template<class InputIterator>
            path(InputIterator first, InputIterator last,
                 format fmt = auto_format)
                : path_{first, last}
            { /* DUMMY BODY */ }

            template<class Source>
            path(const Source& src, const locale& loc, format fmt = auto_format)
                : path_{}
            {
                path_ = LIBCPP_CONVERT_ENC(src, loc);
            }

            template<class InputIterator>
            path(InputIterator first, InputIterator last, const locale& loc,
                 format fmt = auto_format)
                : path_{}
            {
                path_ = LIBCPP_CONVERT_ENC_RANGE(first, last, loc);
            }

            ~path() = default;

            /**
             * [n4659] 30.10.8.4.2, assignments:
             */

            path& operator=(const path& p);
            path& operator=(path&& p) noexcept;
            path& operator=(string_type&& src);
            path& assign(string_type&& src);

            template<class Source>
            path& operator=(const Source& src)
            {
                path_ = LIBCPP_CONVERT_ENC(src, locale{});

                return *this;
            }

            template<class Source>
            path& assign(const Source& src)
            {
                return (*this = src);
            }

            template<class InputIterator>
            path& assign(InputIterator first, InputIterator last)
            {
                path_ = LIBCPP_CONVERT_ENC_RANGE(first, last, locale{});
            }

            /**
             * [n4659] 30.10.8.4.3, appends:
             */

            path& operator/=(const path& p);

            template<class Source>
            path& operator/=(const Source& src)
            {
                return operator/=(path{src});
            }

            template<class Source>
            path& append(const Source& src)
            {
                return operator/=(path{src});
            }

            template<class InputIterator>
            path& append(InputIterator first, InputIterator last)
            {
                return operator/=(path{first, last});
            }

            /**
             * [n4659] 30.10.8.4.4, concatenation:
             */

            path& operator+=(const path& p);
            path& operator+=(const string_type& src);
            /* path& operator+=(basic_string_view<value_type> src); */
            path& operator+=(const value_type* src);
            path& operator+=(value_type c);

            template<class Source>
            path& operator+=(const Source& src)
            {
                path_.append(path{src}.native());

                return *this;
            }

            template<class Char>
            path& operator+=(Char c)
            {
                path_.append(path{c}.native());

                return *this;
            }

            template<class Source>
            path& concat(const Source& src)
            {
                path_.append(path{src}.native());
            }

            template<class InputIterator>
            path& concat(InputIterator first, InputIterator last)
            {
                return *this += path{first, last};
            }

            /**
             * [n4659] 30.10.8.4.5, modifiers:
             */

            void clear() noexcept
            {
                path_.clear();
            }

            path& make_preferred();
            path& remove_filename();
            path& replace_filename(const path& replacement);
            path& replace_extension(const path& replacement = path{});

            void swap(path& p) noexcept
            {
                path_.swap(p.path_);
            }

            /**
             * [n4659] 30.10.8.4.6, native format observers:
             */

            const string_type& native() const noexcept
            {
                return path_;
            }

            const value_type* c_str() const noexcept
            {
                return path_.c_str();
            }

            operator string_type() const
            {
                return path_;
            }

            // TODO: shall not participate unless Char encoded
            template<
                class Char, class Traits = char_traits<Char>,
                class Alloc = allocator<Char>
            >
            basic_string<Char, Traits, Alloc>
            string(const Alloc& alloc = Alloc{}) const
            {
                return basic_string<
                    Char, Traits, Alloc
                >{native(), alloc};
            }

            std::string string() const;
            std::wstring wstring() const;
            /* std::u8string u8string() const; */
            /* std::u16string u16string() const; */
            /* std::u32string u32string() const; */

            /**
             * [n4659] 30.10.8.4.7, generic format observers:
             */

            // TODO: shall not participate unless Char encoded
            template<
                class Char, class Traits = char_traits<Char>,
                class Alloc = allocator<Char>
            >
            basic_string<Char, Traits, Alloc>
            generic_string(const Alloc& alloc = Alloc{}) const
            {
                return path::string(alloc);
            }

            std::string generic_string() const;
            std::wstring generic_wstring() const;
            /* std::u8string generic_u8string() const; */
            /* std::u16string generic_u16string() const; */
            /* std::u32string generic_u32string() const; */

            /**
             * [n4659] 30.10.8.4.8, compare:
             */

            int compare(const path& p) const noexcept;
            int compare(const string_type& str) const;
            /* int compare(basic_string_view<value_type> str) const; */
            int compare(const value_type* str) const;

            /**
             * [n4659] 30.10.8.4.9, decomposition:
             */

            path root_name() const;
            path root_directory() const;
            path root_path() const;
            path relative_path() const;
            path parent_path() const;
            path filename() const;
            path stem() const;
            path extension() const;

            /**
             * [n4659] 30.10.8.4.10, query:
             */

            bool empty() const noexcept
            {
                return path_.empty();
            }

            bool has_root_name() const;
            bool has_root_directory() const;
            bool has_root_path() const;
            bool has_relative_path() const;
            bool has_parent_path() const;
            bool has_filename() const;
            bool has_stem() const;
            bool has_extension() const;
            bool is_absolute() const;
            bool is_relative() const;

            /**
             * [n4659] 30.10.8.4.11, generation:
             */

            path lexically_normal() const;
            path lexically_relative(const path& base) const;
            path lexically_proximate(const path& base) const;

            /**
             * [n4659] 30.10.8.5, iterators:
             */

            class iterator
            {
                public:
                    using iterator_category = bidirectional_iterator_tag;
                    using value_type = path;
                    using difference_type = size_t;
                    using pointer = path* const;
                    using reference = const path&;

                    iterator()
                        : idx_{}, size_{}, elements_{}
                    { /* DUMMY BODY */ }

                    iterator(const path& p, bool end = false);
                    iterator(const iterator& it);
                    iterator& operator=(const iterator& it);
                    iterator(iterator&&);
                    iterator& operator=(iterator&&);

                    ~iterator()
                    {
                        if (elements_)
                            delete[] elements_;
                    }

                    iterator operator++(int)
                    {
                        auto tmp = *this;
                        ++(*this);

                        return tmp;
                    }

                    iterator& operator++()
                    {
                        if (idx_ < size_)
                            ++idx_;

                        return *this;
                    }

                    iterator operator--(int)
                    {
                        auto tmp = *this;
                        --(*this);

                        return tmp;
                    }

                    iterator& operator--()
                    {
                        if (0U < idx_)
                            --idx_;

                        return *this;
                    }

                    reference operator*()
                    {
                        return elements_[idx_];
                    }

                    pointer operator->()
                    {
                        return &elements_[idx_];
                    }

                    bool operator==(const iterator& it);

                    bool operator!=(const iterator& it)
                    {
                        return !(*this == it);
                    }

                private:
                    size_t idx_;
                    size_t size_;
                    path* elements_;

                    bool has_trailing_element_(const string_type&);
                    size_t get_element_count_(const string_type&);
                    path* split_path_to_elements_(const string_type&, size_t);
            };

            using const_iterator = iterator;

            iterator begin() const;
            iterator end() const;

        private:
            string_type path_;

            friend bool operator==(const path&, const path&);
            friend size_t hash_value(const path&);
    };

    /**
     * [n4659] 30.10.8.6, path non-member functions:
     */

    void swap(path& lhs, path& rhs) noexcept;
    size_t hash_value(const path& p) noexcept;

    bool operator==(const path& lhs, const path& rhs) noexcept;
    bool operator!=(const path& lhs, const path& rhs) noexcept;
    bool operator<(const path& lhs, const path& rhs) noexcept;
    bool operator<=(const path& lhs, const path& rhs) noexcept;
    bool operator>(const path& lhs, const path& rhs) noexcept;
    bool operator>=(const path& lhs, const path& rhs) noexcept;

    path operator/(const path& lhs, const path& rhs);

    /**
     * [n4659] 30.10.8.6.1, path inserter and extractor:
     */

    template<class Char, class Traits>
    basic_ostream<Char, Traits>&
    operator<<(basic_ostream<Char, Traits>& os, const path& p)
    {
        // Note: Should be using quoted(), which is not implemented.
        os << p.string<Char, Traits>();

        return os;
    }

    template<class Char, class Traits>
    basic_istream<Char, Traits>&
    operator>>(basic_istream<Char, Traits>& is, path& p)
    {
        // Note: Should be using quoted(), which is not implemented.
        basic_string<Char, Traits> str{};
        is >> str;

        p = path{str};

        return is;
    }

    /**
     * [n4659] 30.10.8.6.2, path factory functions:
     * Note: These do no conversions as of now as libcpp
     *       does not fully take UTF-8 into account.
     */

    template<class Source>
    path u8path(const Source& s)
    {
        return path{s};
    }

    template<class InputIterator>
    path u8path(InputIterator first, InputIterator last)
    {
        return path{first, last};
    }
}

#endif
