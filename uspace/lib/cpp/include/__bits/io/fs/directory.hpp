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

#ifndef LIBCPP_BITS_IO_FS_DIRECTORY
#define LIBCPP_BITS_IO_FS_DIRECTORY

#include <__bits/io/fs/filesystem.hpp>
#include <__bits/io/fs/path.hpp>
#include <cstdlib>
#include <dirent.h>
#include <stack>

namespace std
{
    class error_code;
}

namespace std::filesystem
{

    namespace aux
    { // For brevity since we need to use it for path.
        namespace fs = ::std::filesystem;
    }

    /**
     * [n4659] 30.10.12, directory entries:
     */

    class directory_entry
    {
        public:
            directory_entry() noexcept = default;
            directory_entry(const directory_entry&) = default;
            directory_entry(directory_entry&&) noexcept = default;

            explicit directory_entry(const aux::fs::path& p);
            directory_entry(const aux::fs::path& p, error_code& ec);

            ~directory_entry() = default;

            directory_entry& operator=(const directory_entry&) = default;
            directory_entry& operator=(directory_entry&&) noexcept = default;

            void assign(const aux::fs::path& p);
            void assign(const aux::fs::path& p, error_code& ec);
            void replace_filename(const aux::fs::path& p);
            void replace_filename(const aux::fs::path& p, error_code& ec);
            void refresh();
            void refresh(error_code& ec) noexcept;

            const aux::fs::path& path() const noexcept;
            operator const aux::fs::path&() const noexcept;
            bool exists() const;
            bool exists(error_code& ec) const noexcept;
            bool is_block_file() const;
            bool is_block_file(error_code& ec) const noexcept;
            bool is_character_file() const;
            bool is_character_file(error_code& ec) const noexcept;
            bool is_directory() const;
            bool is_directory(error_code& ec) const noexcept;
            bool is_fifo() const;
            bool is_fifo(error_code& ec) const noexcept;
            bool is_other() const;
            bool is_other(error_code& ec) const noexcept;
            bool is_regular_file() const;
            bool is_regular_file(error_code& ec) const noexcept;
            bool is_socket() const;
            bool is_socket(error_code& ec) const noexcept;
            bool is_symlink() const;
            bool is_symlink(error_code& ec) const noexcept;
            uintmax_t file_size() const;
            uintmax_t file_size(error_code& ec) const noexcept;
            uintmax_t hard_link_count() const;
            uintmax_t hard_link_count(error_code& ec) const noexcept;
            file_time_type last_write_time() const;
            file_time_type last_write_time(error_code& ec) const noexcept;
            file_status status() const;
            file_status status(error_code& ec) const noexcept;
            file_status symlink_status() const;
            file_status symlink_status(error_code& ec) const noexcept;

            bool operator<(const directory_entry& rhs) const noexcept;
            bool operator==(const directory_entry& rhs) const noexcept;
            bool operator!=(const directory_entry& rhs) const noexcept;
            bool operator<=(const directory_entry& rhs) const noexcept;
            bool operator>(const directory_entry& rhs) const noexcept;
            bool operator>=(const directory_entry& rhs) const noexcept;

        private:
            aux::fs::path path_;

            /**
             * TODO: Add attribute caching.
             */

            friend class directory_iterator;
    };

    /**
     * [n4659] 30.10.13, directory iterators:
     */

    class directory_iterator
    {
        public:
            using iterator_category = input_iterator_tag;
            using value_type        = directory_entry;
            using difference_type   = ptrdiff_t;
            using pointer           = const directory_entry*;
            using reference         = const directory_entry&;

            directory_iterator() noexcept;
            explicit directory_iterator(const path& p);
            directory_iterator(const path& p, directory_options opts);
            directory_iterator(const path& p, error_code& ec) noexcept;
            directory_iterator(const path& p, directory_options opts,
                               error_code& ec) noexcept;

            directory_iterator(const directory_iterator& rhs);
            directory_iterator(directory_iterator&& rhs) noexcept;
            ~directory_iterator();

            directory_iterator& operator=(const directory_iterator& rhs);
            directory_iterator& operator=(directory_iterator&& rhs) noexcept;

            reference operator*() const;
            pointer operator->() const;
            directory_iterator operator++(int);
            directory_iterator& operator++();
            directory_iterator& increment(error_code& ec) noexcept;
            bool operator!=(const directory_iterator& rhs) const noexcept;

        private:
            /**
             * This field need to be mutable as during copying
             * it has to be changed to nullptr in the original
             * iterator. This is to avoid double free in
             * closedir caused by that old copy gets destroyed.
             */
            mutable DIR* dir_;
            directory_entry curr_;
    };

    /**
     * [n4659] 30.10.13.2, range access for directory iterators:
     */

    directory_iterator begin(directory_iterator it) noexcept;
    directory_iterator end(const directory_iterator&) noexcept;

    /**
     * [n4659] 30.10.14, recursive directory iterators:
     */

    class recursive_directory_iterator
    {
        public:
            using iterator_category = input_iterator_tag;
            using value_type        = directory_entry;
            using difference_type   = ptrdiff_t;
            using pointer           = const directory_entry*;
            using reference         = const directory_entry&;

            recursive_directory_iterator() noexcept;
            explicit recursive_directory_iterator(const path& p);
            recursive_directory_iterator(const path& p, directory_options opts);
            recursive_directory_iterator(const path& p, directory_options opts,
                                         error_code& ec) noexcept;
            recursive_directory_iterator(const path& p, error_code& ec) noexcept;

            recursive_directory_iterator(
                const recursive_directory_iterator& rhs);
            recursive_directory_iterator(
                recursive_directory_iterator&& rhs) noexcept;
            ~recursive_directory_iterator();

            recursive_directory_iterator&
            operator=(const recursive_directory_iterator& rhs);
            recursive_directory_iterator&
            operator=(recursive_directory_iterator&& rhs) noexcept;

            directory_options options() const;
            int depth() const;
            bool recursion_pending() const;

            reference operator*() const;
            pointer operator->() const;
            recursive_directory_iterator operator++(int);
            recursive_directory_iterator& operator++();
            recursive_directory_iterator& increment(error_code& ec) noexcept;
            bool operator!=(const recursive_directory_iterator& rhs)
                const noexcept;

            void pop();
            void pop(error_code& ec) noexcept;
            void disable_recursion_pending();

        private:
            directory_options opts_;
            bool rec_pending_;

            mutable DIR* dir_;
            directory_entry curr_;

            std::stack<DIR*> dir_stack_{};

            bool should_enter_subdir_() const;
            int increment_();
    };

    /**
     * [n4659] 30.14.2, range access for recursive directory iterators:
     */

    recursive_directory_iterator
    begin(recursive_directory_iterator it) noexcept;

    recursive_directory_iterator
    end(const recursive_directory_iterator&) noexcept;
}

#endif
