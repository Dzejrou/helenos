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

#ifndef LIBCPP_BITS_IO_FS_FILESYSTEM
#define LIBCPP_BITS_IO_FS_FILESYSTEM

#include <chrono>
#include <cstdlib>
#include <iosfwd>
#include <locale>
#include <string>

// TODO: explain these, path conversion might not be needed
//       as for us native == generic (POSIX paths)
//       also: remove any use of native <-> generic conversions
//       as helenos does need it
#define LIBCPP_CONVERT_PATH(fmt) /* Ignored. */
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

// TODO: add default function arguments
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
             */

            // TODO: add a note about formats and what they mean for us
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
            {
                LIBCPP_CONVERT_PATH(fmt);
            }

            template<class InputIterator>
            path(InputIterator first, InputIterator last,
                 format fmt = auto_format)
                : path_{first, last}
            {
                LIBCPP_CONVERT_PATH(fmt);
            }

            template<class Source>
            path(const Source& src, const locale& loc, format fmt = auto_format)
                : path_{}
            {
                path_ = LIBCPP_CONVERT_ENC(src, loc);
                LIBCPP_CONVERT_PATH(fmt);
            }

            template<class InputIterator>
            path(InputIterator first, InputIterator last, const locale& loc,
                 format fmt = auto_format)
                : path_{}
            {
                path_ = LIBCPP_CONVERT_ENC_RANGE(first, last, loc);
                LIBCPP_CONVERT_PATH(fmt);
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
                    using value_type = path;
                    using reference = const path&;
                    using difference_type = size_t;
                    using pointer = path* const;

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

                /* private: */
                    size_t idx_;
                    size_t size_;
                    path* elements_;
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
        os << p.native();

        return os;
    }

    template<class Char, class Traits>
    basic_istream<Char, Traits>&
    operator>>(basic_istream<Char, Traits>& is, path& p)
    {
        basic_string<Char, Traits> str{};
        is >> str;

        p = path{str};

        return is;
    }

    /**
     * [n4659] 30.10.8.6.2, path factory functions:
     */

    template<class Source>
    path u8path(const Source& s)
    {
        // TODO:
    }

    template<class InputIterator>
    path u8path(InputIterator first, InputIterator last)
    {
        // TODO:
    }

    /**
     * [n4659] 30.10.9, filesystem errors:
     */

    class filesystem_error
    {
        // TODO:
    };

    /**
     * [n4659] 30.10.12, directory entries:
     */

    class directory_entry
    {
        // TODO:
    };

    /**
     * [n4659] 30.10.13, directory iterators:
     */

    class directory_iterator
    {
        // TODO:
    };

    /**
     * [n4659] 30.10.13.2, range access for directory iterators:
     */

    directory_iterator begin(directory_iterator it) noexcept;
    directory_iterator end(const directory_iterator& it) noexcept;

    /**
     * [n4659] 30.10.14, recursive directory iterators:
     */

    class recursive_directory_iterator
    {
        // TODO:
    };

    /**
     * [n4659] 30.14.2, range access for recursive directory iterators:
     */

    recursive_directory_iterator
    begin(recursive_directory_iterator it) noexcept;

    recursive_directory_iterator
    end(const recursive_directory_iterator& it) noexcept;

    /**
     * [n4659] 30.10.11, file status:
     */

    class file_status
    {
        // TODO:
    };

    struct space_info
    {
        uintmax_t capacity;
        uintmax_t free;
        uintmax_t available;
    };

    /**
     * [n4659] 30.10.10 enumerations:
     */

    enum class file_type
    {
        // TODO:
    };

    enum class perms
    {
        // TODO:
    };

    enum class perm_options
    {
        // TODO:
    };

    enum class copy_options
    {
        // TODO:
    };

    enum class directory_options
    {
        // TODO:
    };

    using file_time_type = chrono::time_point<void, void /* TODO: trivial clock */>;

    /**
     * [n4659] 30.10.15, filesystem operations:
     */

    path absolute(const path& p, const path& base);

    path canonical(const path& p, const path& base);
    path canonical(const path& p, error_code& ec);
    path canonical(const path& p, const path& base, error_code& ec);

    void copy(const path& from, const path& to);
    void copy(const path& from, const path& to, error_code& ec) noexcept;
    void copy(const path& from, const path& to, copy_options option);
    void copy(const path& from, const path& to,
              copy_options option, error_code& ec) noexcept;

    void copy_file(const path& from, const path& to);
    void copy_file(const path& from, const path& to, error_code& ec) noexcept;
    void copy_file(const path& from, const path& to, copy_options option);
    void copy_file(const path& from, const path& to,
                   copy_options option, error_code& ec) noexcept;

    void copy_symlink(const path& from, const path& to);
    void copy_symlink(const path& from, const path& to, error_code& ec) noexcept;

    bool create_directories(const path& p);
    bool create_directories(const path& p, error_code& ec) noexcept;

    bool create_directory(const path& p);
    bool create_directory(const path& p, const path& attrib);

    bool create_directory(const path& p, const path& attrib);
    bool create_directory(const path& p, const path& attrib,
                          error_code& ec) noexcept;

    void create_directory_symlink(const path& to, const path& new_symlink);
    void create_directory_symlink(const path& to, const path& new_symlink,
                                  error_code& ec) noexcept;

    void create_hard_link(const path& to, const path& new_hard_link);
    void create_hard_link(const path& to, const path& new_hard_link,
                          error_code& ec) noexcept;

    void create_symlink(const path& to, const path& new_symlink);
    void create_symlink(const path& to, const path& new_symlink,
                        error_code& ec) noexcept;

    path current_path();
    path current_path(error_code& ec) noexcept;
    void current_path(const path& p);
    void current_path(const path& p, error_code& ec) noexcept;

    bool exists(file_status s) noexcept;
    bool exists(const path& p);
    bool exists(const path& p, error_code& ec) noexcept;

    bool equivalent(const path& p1, const path& p2);
    bool equivalent(const path& p1, const path& p2, error_code& ec) noexcept;

    uintmax_t file_size(const path& p);
    uintmax_t file_size(const path& p, error_code& ec) noexcept;

    uintmax_t hard_link_count(const path& p);
    uintmax_t hard_link_count(const path& p, error_code& ec) noexcept;

    bool is_block_file(file_status s) noexcept;
    bool is_block_file(const path& p);
    bool is_block_file(const path& p, error_code& ec) noexcept;

    bool is_character_file(file_status s) noexcept;
    bool is_character_file(const path& p);
    bool is_character_file(const path& p, error_code& ec) noexcept;

    bool is_directory(file_status s) noexcept;
    bool is_directory(const path& p);
    bool is_directory(const path& p, error_code& ec) noexcept;

    bool is_empty(const path& p);
    bool is_empty(const path& p, error_code& ec) noexcept;

    bool is_fifo(file_status s) noexcept;
    bool is_fifo(const path& p);
    bool is_fifo(const path& p, error_code& ec) noexcept;

    bool is_other(file_status s) noexcept;
    bool is_other(const path& p);
    bool is_other(const path& p, error_code& ec) noexcept;

    bool is_regular_file(file_status s) noexcept;
    bool is_regular_file(const path& p);
    bool is_regular_file(const path& p, error_code& ec) noexcept;

    bool is_socket(file_status s) noexcept;
    bool is_socket(const path& p);
    bool is_socket(const path& p, error_code& ec) noexcept;

    bool is_symlink(file_status s) noexcept;
    bool is_symlink(const path& p);
    bool is_symlink(const path& p, error_code& ec) noexcept;

    file_time_type last_write_time(const path& p);
    file_time_type last_write_time(const path& p, error_code& ec) noexcept;

    void last_write_time(const path& p, file_time_type new_time);
    void last_write_time(const path& p, file_time_type new_time,
                         error_code& ec) noexcept;

    void permissions(const path& p, perms prms,
                     perm_options opts);
    void permissions(const path& p, perms prms, error_code& ec) noexcept;
    void permissions(const path& p, perms prms, perm_options opts,
                     error_code& ec) noexcept;

    path proximate(const path& p, error_code& ec);
    path proximate(const path& p, const path& base);
    path proximate(const path& p, const path& base, error_code& ec);

    path read_symlink(const path& p);
    path read_symlink(const path& p, error_code& ec);

    path relative(const path& p, error_code& ec);
    path relative(const path& p, const path& base);
    path relative(const path& p, const path& base, error_code& ec);

    bool remove(const path& p);
    bool remove(const path& p, error_code& ec) noexcept;

    uintmax_t remove_all(const path& p);
    uintmax_t remove_all(const path& p, error_code& ec) noexcept;

    void rename(const path& from, const path& to);
    void rename(const path& from, const path& to, error_code& ec) noexcept;

    void resize_file(const path& p, uintmax_t size);
    void resize_file(const path& p, uintmax_t size, error_code& ec) noexcept;

    space_info space(const path& p);
    space_info space(const path& p, error_code& ec);

    file_status status(const path& p);
    file_status status(const path& p, error_code& ec) noexcept;

    bool status_known(file_status s) noexcept;

    file_status symlink_status(const path& p);
    file_status symlink_status(const path& p, error_code& ec) noexcept;

    path temp_directory_path();
    path temp_directory_path(error_code& ec) noexcept;

    file_status symlink_status(const path& p);
    file_status symlink_status(const path& p, error_code& ec) noexcept;

    path temp_directory_path();
    path temp_directory_path(error_code& ec);

    path weakly_canonical(const path& p);
    path weakly_canonical(const path& p, error_code& ec);
}

#endif
