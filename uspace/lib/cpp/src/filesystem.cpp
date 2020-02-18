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
#include <cassert>

namespace std::filesystem
{
    filesystem_error::filesystem_error(const string& msg, error_code ec)
        : system_error{ec}, msg_{msg}, p1_{}, p2_{}
    { /* DUMMY BODY */ }

    filesystem_error::filesystem_error(const string& msg, const path& p,
                                       error_code ec)
        : system_error{ec}, msg_{msg}, p1_{p}, p2_{}
    { /* DUMMY BODY */ }

    filesystem_error::filesystem_error(const string& msg, const path& p1,
                                       const path& p2, error_code ec)
        : system_error{ec}, msg_{msg}, p1_{p1}, p2_{p2}
    { /* DUMMY BODY */ }

    const path& filesystem_error::path1() const noexcept
    {
        return p1_;
    }

    const path& filesystem_error::path2() const noexcept
    {
        return p2_;
    }

    const char* filesystem_error::what() const noexcept
    {
        return msg_.c_str();
    }

    path absolute(const path& p, const path& base)
    {
        // TODO:
        __unimplemented();

        return {};
    }

    path canonical(const path& p, const path& base)
    {
        // TODO:
        __unimplemented();

        return {};
    }

    path canonical(const path& p, error_code& ec)
    {
        // TODO:
        __unimplemented();

        return {};
    }

    path canonical(const path& p, const path& base, error_code& ec)
    {
        // TODO:
        __unimplemented();

        return {};
    }

    void copy(const path& from, const path& to)
    {
        // TODO:
        __unimplemented();
    }

    void copy(const path& from, const path& to, error_code& ec) noexcept
    {
        // TODO:
        __unimplemented();
    }

    void copy(const path& from, const path& to, copy_options option)
    {
        // TODO:
        __unimplemented();
    }

    void copy(const path& from, const path& to,
              copy_options option, error_code& ec) noexcept
    {
        // TODO:
        __unimplemented();
    }

    void copy_file(const path& from, const path& to)
    {
        // TODO:
        __unimplemented();
    }

    void copy_file(const path& from, const path& to, error_code& ec) noexcept
    {
        // TODO:
        __unimplemented();
    }

    void copy_file(const path& from, const path& to, copy_options option)
    {
        // TODO:
        __unimplemented();
    }

    void copy_file(const path& from, const path& to,
                   copy_options option, error_code& ec) noexcept
    {
        // TODO:
        __unimplemented();
    }

    void copy_symlink(const path& from, const path& to)
    {
        // TODO:
        __unimplemented();
    }

    void copy_symlink(const path& from, const path& to, error_code& ec) noexcept
    {
        // TODO:
        __unimplemented();
    }

    bool create_directories(const path& p)
    {
        // TODO:
        __unimplemented();

        return {};
    }

    bool create_directories(const path& p, error_code& ec) noexcept
    {
        // TODO:
        __unimplemented();

        return {};
    }

    bool create_directory(const path& p)
    {
        // TODO:
        __unimplemented();

        return {};
    }

    bool create_directory(const path& p, const error_code& ec)
    {
        // TODO:
        __unimplemented();

        return {};
    }

    bool create_directory(const path& p, const path& attrib)
    {
        // TODO:
        __unimplemented();

        return {};
    }

    bool create_directory(const path& p, const path& attrib,
                          error_code& ec) noexcept
    {
        // TODO:
        __unimplemented();

        return {};
    }

    void create_directory_symlink(const path& to, const path& new_symlink)
    {
        // TODO:
        __unimplemented();
    }

    void create_directory_symlink(const path& to, const path& new_symlink,
                                  error_code& ec) noexcept
    {
        // TODO:
        __unimplemented();
    }

    void create_hard_link(const path& to, const path& new_hard_link)
    {
        // TODO:
        __unimplemented();
    }

    void create_hard_link(const path& to, const path& new_hard_link,
                          error_code& ec) noexcept
    {
        // TODO:
        __unimplemented();
    }

    void create_symlink(const path& to, const path& new_symlink)
    {
        // TODO:
        __unimplemented();
    }

    void create_symlink(const path& to, const path& new_symlink,
                        error_code& ec) noexcept
    {
        // TODO:
        __unimplemented();
    }

    path current_path()
    {
        // TODO:
        __unimplemented();

        return {};
    }

    path current_path(error_code& ec) noexcept
    {
        // TODO:
        __unimplemented();

        return {};
    }

    void current_path(const path& p)
    {
        // TODO:
        __unimplemented();
    }

    void current_path(const path& p, error_code& ec) noexcept
    {
        // TODO:
        __unimplemented();
    }

    bool exists(file_status s) noexcept
    {
        // TODO:
        __unimplemented();

        return {};
    }

    bool exists(const path& p)
    {
        // TODO:
        __unimplemented();

        return {};
    }

    bool exists(const path& p, error_code& ec) noexcept
    {
        // TODO:
        __unimplemented();

        return {};
    }

    bool equivalent(const path& p1, const path& p2)
    {
        // TODO:
        __unimplemented();

        return {};
    }

    bool equivalent(const path& p1, const path& p2, error_code& ec) noexcept
    {
        // TODO:
        __unimplemented();

        return {};
    }

    uintmax_t file_size(const path& p)
    {
        // TODO:
        __unimplemented();

        return {};
    }

    uintmax_t file_size(const path& p, error_code& ec) noexcept
    {
        // TODO:
        __unimplemented();

        return {};
    }

    uintmax_t hard_link_count(const path& p)
    {
        // TODO:
        __unimplemented();

        return {};
    }

    uintmax_t hard_link_count(const path& p, error_code& ec) noexcept
    {
        // TODO:
        __unimplemented();

        return {};
    }

    bool is_block_file(file_status s) noexcept
    {
        // TODO:
        __unimplemented();

        return {};
    }

    bool is_block_file(const path& p)
    {
        // TODO:
        __unimplemented();

        return {};
    }

    bool is_block_file(const path& p, error_code& ec) noexcept
    {
        // TODO:
        __unimplemented();

        return {};
    }

    bool is_character_file(file_status s) noexcept
    {
        // TODO:
        __unimplemented();

        return {};
    }

    bool is_character_file(const path& p)
    {
        // TODO:
        __unimplemented();

        return {};
    }

    bool is_character_file(const path& p, error_code& ec) noexcept
    {
        // TODO:
        __unimplemented();

        return {};
    }

    bool is_directory(file_status s) noexcept
    {
        // TODO:
        __unimplemented();

        return {};
    }

    bool is_directory(const path& p)
    {
        // TODO:
        __unimplemented();

        return {};
    }

    bool is_directory(const path& p, error_code& ec) noexcept
    {
        // TODO:
        __unimplemented();

        return {};
    }

    bool is_empty(const path& p)
    {
        // TODO:
        __unimplemented();

        return {};
    }

    bool is_empty(const path& p, error_code& ec) noexcept
    {
        // TODO:
        __unimplemented();

        return {};
    }

    bool is_fifo(file_status s) noexcept
    {
        // TODO:
        __unimplemented();

        return {};
    }

    bool is_fifo(const path& p)
    {
        // TODO:
        __unimplemented();

        return {};
    }

    bool is_fifo(const path& p, error_code& ec) noexcept
    {
        // TODO:
        __unimplemented();

        return {};
    }

    bool is_other(file_status s) noexcept
    {
        // TODO:
        __unimplemented();

        return {};
    }

    bool is_other(const path& p)
    {
        // TODO:
        __unimplemented();

        return {};
    }

    bool is_other(const path& p, error_code& ec) noexcept
    {
        // TODO:
        __unimplemented();

        return {};
    }

    bool is_regular_file(file_status s) noexcept
    {
        // TODO:
        __unimplemented();

        return {};
    }

    bool is_regular_file(const path& p)
    {
        // TODO:
        __unimplemented();

        return {};
    }

    bool is_regular_file(const path& p, error_code& ec) noexcept
    {
        // TODO:
        __unimplemented();

        return {};
    }

    bool is_socket(file_status s) noexcept
    {
        // TODO:
        __unimplemented();

        return {};
    }

    bool is_socket(const path& p)
    {
        // TODO:
        __unimplemented();

        return {};
    }

    bool is_socket(const path& p, error_code& ec) noexcept
    {
        // TODO:
        __unimplemented();

        return {};
    }

    bool is_symlink(file_status s) noexcept
    {
        // TODO:
        __unimplemented();

        return {};
    }

    bool is_symlink(const path& p)
    {
        // TODO:
        __unimplemented();

        return {};
    }

    bool is_symlink(const path& p, error_code& ec) noexcept
    {
        // TODO:
        __unimplemented();

        return {};
    }

    file_time_type last_write_time(const path& p)
    {
        // TODO:
        __unimplemented();

        return {};
    }

    file_time_type last_write_time(const path& p, error_code& ec) noexcept
    {
        // TODO:
        __unimplemented();

        return {};
    }

    void last_write_time(const path& p, file_time_type new_time)
    {
        // TODO:
        __unimplemented();
    }

    void last_write_time(const path& p, file_time_type new_time,
                         error_code& ec) noexcept
    {
        // TODO:
        __unimplemented();
    }

    void permissions(const path& p, perms prms,
                     perm_options opts)
    {
        // TODO:
        __unimplemented();
    }

    void permissions(const path& p, perms prms, error_code& ec) noexcept
    {
        // TODO:
        __unimplemented();
    }

    void permissions(const path& p, perms prms, perm_options opts,
                     error_code& ec) noexcept
    {
        // TODO:
        __unimplemented();
    }

    path proximate(const path& p, error_code& ec)
    {
        // TODO:
        __unimplemented();

        return {};
    }

    path proximate(const path& p, const path& base)
    {
        // TODO:
        __unimplemented();

        return {};
    }

    path proximate(const path& p, const path& base, error_code& ec)
    {
        // TODO:
        __unimplemented();

        return {};
    }

    path read_symlink(const path& p)
    {
        // TODO:
        __unimplemented();

        return {};
    }

    path read_symlink(const path& p, error_code& ec)
    {
        // TODO:
        __unimplemented();

        return {};
    }

    path relative(const path& p, error_code& ec)
    {
        // TODO:
        __unimplemented();

        return {};
    }

    path relative(const path& p, const path& base)
    {
        // TODO:
        __unimplemented();

        return {};
    }

    path relative(const path& p, const path& base, error_code& ec)
    {
        // TODO:
        __unimplemented();

        return {};
    }

    bool remove(const path& p)
    {
        // TODO:
        __unimplemented();

        return {};
    }

    bool remove(const path& p, error_code& ec) noexcept
    {
        // TODO:
        __unimplemented();

        return {};
    }

    uintmax_t remove_all(const path& p)
    {
        // TODO:
        __unimplemented();

        return {};
    }

    uintmax_t remove_all(const path& p, error_code& ec) noexcept
    {
        // TODO:
        __unimplemented();

        return {};
    }

    void rename(const path& from, const path& to)
    {
        // TODO:
        __unimplemented();
    }

    void rename(const path& from, const path& to, error_code& ec) noexcept
    {
        // TODO:
        __unimplemented();
    }

    void resize_file(const path& p, uintmax_t size)
    {
        // TODO:
        __unimplemented();
    }

    void resize_file(const path& p, uintmax_t size, error_code& ec) noexcept
    {
        // TODO:
        __unimplemented();
    }

    space_info space(const path& p)
    {
        // TODO:
        __unimplemented();

        return {};
    }

    space_info space(const path& p, error_code& ec)
    {
        // TODO:
        __unimplemented();

        return {};
    }

    file_status status(const path& p)
    {
        // TODO:
        __unimplemented();

        return {};
    }

    file_status status(const path& p, error_code& ec) noexcept
    {
        // TODO:
        __unimplemented();

        return {};
    }

    bool status_known(file_status s) noexcept
    {
        // TODO:
        __unimplemented();

        return {};
    }

    file_status symlink_status(const path& p)
    {
        // TODO:
        __unimplemented();

        return {};
    }

    file_status symlink_status(const path& p, error_code& ec) noexcept
    {
        // TODO:
        __unimplemented();

        return {};
    }

    path temp_directory_path()
    {
        // TODO:
        __unimplemented();

        return {};
    }

    path temp_directory_path(error_code& ec) noexcept
    {
        // TODO:
        __unimplemented();

        return {};
    }

    path weakly_canonical(const path& p)
    {
        // TODO:
        __unimplemented();

        return {};
    }

    path weakly_canonical(const path& p, error_code& ec)
    {
        // TODO:
        __unimplemented();

        return {};
    }
}
