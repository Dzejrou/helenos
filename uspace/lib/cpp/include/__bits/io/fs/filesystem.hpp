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

#include <__bits/io/fs/path.hpp>
#include <chrono>
#include <cstdlib>
#include <locale>
#include <string>
#include <system_error>

// TODO: add default function arguments
namespace std::filesystem
{
    /**
     * [n4659] 30.10.9, filesystem errors:
     */

    class filesystem_error: public system_error
    {
        public:
            filesystem_error(const string& msg, error_code ec);
            filesystem_error(const string& msg, const path& p,
                             error_code ec);
            filesystem_error(const string& msg, const path& p1,
                             const path& p2, error_code ec);

            const path& path1() const noexcept;
            const path& path2() const noexcept;
            const char* what() const noexcept override;

        private:
            std::string msg_;
            path p1_;
            path p2_;
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
        none,
        not_found,
        regular,
        directory,
        symlink,
        block,
        character,
        fifo,
        socket,
        unknown
    };

    enum class perms
    {
        none = 0,
        owner_read   = 0400,
        owner_write  = 0200,
        owner_exec   = 0100,
        owner_all    = 0700,
        group_read   = 040,
        group_write  = 020,
        group_exec   = 010,
        group_all    = 070,
        others_read  = 04,
        others_write = 02,
        others_exec  = 01,
        others_all   = 07,
        all          = 0777,
        set_uid      = 04000,
        set_gid      = 02000,
        sticky_bit   = 01000,
        mask         = 07777,
        unknown      = 0xFFFF
    };

    inline perms operator&(perms lhs, perms rhs)
    {
        return static_cast<perms>(
            static_cast<int>(lhs) &
            static_cast<int>(rhs)
        );
    }

    inline perms operator|(perms lhs, perms rhs)
    {
        return static_cast<perms>(
            static_cast<int>(lhs) |
            static_cast<int>(rhs)
        );
    }

    inline perms operator^(perms lhs, perms rhs)
    {
        return static_cast<perms>(
            static_cast<int>(lhs) ^
            static_cast<int>(rhs)
        );
    }

    inline perms operator!(perms p)
    {
        return static_cast<perms>(!static_cast<int>(p));
    }

    enum class perm_options
    {
        replace,
        add,
        remove,
        nofollow
    };

    inline perm_options operator&(perm_options lhs, perm_options rhs)
    {
        return static_cast<perm_options>(
            static_cast<int>(lhs) &
            static_cast<int>(rhs)
        );
    }

    inline perm_options operator|(perm_options lhs, perm_options rhs)
    {
        return static_cast<perm_options>(
            static_cast<int>(lhs) |
            static_cast<int>(rhs)
        );
    }

    inline perm_options operator^(perm_options lhs, perm_options rhs)
    {
        return static_cast<perm_options>(
            static_cast<int>(lhs) ^
            static_cast<int>(rhs)
        );
    }

    inline perm_options operator!(perm_options p)
    {
        return static_cast<perm_options>(!static_cast<int>(p));
    }

    enum class copy_options
    {
        none,

        // Files
        skip_existing,
        overwrite_existing,
        update_existing,

        // Sub-directories
        recursive,

        // Symbolic links
        copy_symlinks,
        skip_symlinks,

        // Form of copying
        directories_only,
        create_symlinks,
        create_hard_links
    };

    inline copy_options operator&(copy_options lhs, copy_options rhs)
    {
        return static_cast<copy_options>(
            static_cast<int>(lhs) &
            static_cast<int>(rhs)
        );
    }

    inline copy_options operator|(copy_options lhs, copy_options rhs)
    {
        return static_cast<copy_options>(
            static_cast<int>(lhs) |
            static_cast<int>(rhs)
        );
    }

    inline copy_options operator^(copy_options lhs, copy_options rhs)
    {
        return static_cast<copy_options>(
            static_cast<int>(lhs) ^
            static_cast<int>(rhs)
        );
    }

    inline copy_options operator!(copy_options c)
    {
        return static_cast<copy_options>(!static_cast<int>(c));
    }

    enum class directory_options
    {
        none,
        follow_directory_symlink,
        skip_permission_denied
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
