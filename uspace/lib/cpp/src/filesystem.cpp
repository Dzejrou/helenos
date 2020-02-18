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
#include <string>

namespace helenos
{ // TODO: Fix this directly in libc.
    typedef uint64_t aoff64_t;
    extern "C" {
        #include <vfs/vfs.h>
    }
}

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
        char buf[256];
        auto rc = helenos::vfs_cwd_get(buf, 256U);
        if (rc != EOK)
        {
            assert(rc == ERANGE);
            throw LIBCPP_FSYSTEM_EXCEPT(errc::result_out_of_range);
        }

        return path{string{&buf[0]}};
    }

    path current_path(error_code& ec) noexcept
    {
        char buf[256];
        auto rc = helenos::vfs_cwd_get(buf, 256U);
        if (rc != EOK)
        {
            LIBCPP_SET_ERRCODE(errc::result_out_of_range);
            return path{};
        }
        else
            ec.clear();

        return path{string{&buf[0]}};
    }

    void current_path(const path& p)
    {
        auto rc = helenos::vfs_cwd_set(p.string().c_str());
        if (rc != EOK)
            LIBCPP_FSYSTEM_THROW(rc, p);
    }

    void current_path(const path& p, error_code& ec) noexcept
    {
        auto rc = helenos::vfs_cwd_set(p.string().c_str());
        if (rc != EOK)
            LIBCPP_SET_ERRCODE(rc);
        else
            ec.clear();
    }

    bool exists(file_status s) noexcept
    {
        return status_known(s) && s.type() != file_type::not_found;
    }

    bool exists(const path& p)
    {
        return exists(status(p));
    }

    bool exists(const path& p, error_code& ec) noexcept
    {
        auto s = status(p);
        if (status_known(s))
            ec.clear();

        return exists(s);
    }

    bool equivalent(const path& p1, const path& p2)
    {
        auto s1 = status(p1);
        auto s2 = status(p2);

        if (!exists(s1) || !exists(s2) || (is_other(s1) && is_other(s2)))
            LIBCPP_FSYSTEM_THROW(ENOENT, p1, p2);

        // TODO: s1 == s2 and p1 and p2 point to the same place.
        return false;
    }

    bool equivalent(const path& p1, const path& p2, error_code& ec) noexcept
    {
        auto s1 = status(p1);
        auto s2 = status(p2);

        if (!exists(s1) || !exists(s2) || (is_other(s1) && is_other(s2)))
        {
            LIBCPP_SET_ERRCODE(ENOENT);

            return false;
        }

        // TODO: s1 == s2 and p1 and p2 point to the same place.
        return false;
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
        return s.type() == file_type::block;
    }

    bool is_block_file(const path& p)
    {
        return is_block_file(status(p));
    }

    bool is_block_file(const path& p, error_code& ec) noexcept
    {
        auto s = status(p, ec);

        if (!ec)
            return false;
        return is_block_file(s);
    }

    bool is_character_file(file_status s) noexcept
    {
        return s.type() == file_type::character;
    }

    bool is_character_file(const path& p)
    {
        return is_character_file(status(p));
    }

    bool is_character_file(const path& p, error_code& ec) noexcept
    {
        auto s = status(p, ec);

        if (!ec)
            return false;
        return is_character_file(s);
    }

    bool is_directory(file_status s) noexcept
    {
        return s.type() == file_type::directory;
    }

    bool is_directory(const path& p)
    {
        return is_directory(status(p));
    }

    bool is_directory(const path& p, error_code& ec) noexcept
    {
        auto s = status(p, ec);

        if (!ec)
            return false;
        return is_directory(s);
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
        return s.type() == file_type::fifo;
    }

    bool is_fifo(const path& p)
    {
        return is_fifo(status(p));
    }

    bool is_fifo(const path& p, error_code& ec) noexcept
    {
        auto s = status(p, ec);

        if (!ec)
            return false;
        return is_fifo(s);
    }

    bool is_other(file_status s) noexcept
    {
        return exists(s) && !is_regular_file(s) && !is_directory(s)
            && !is_symlink(s);
    }

    bool is_other(const path& p)
    {
        return is_other(status(p));
    }

    bool is_other(const path& p, error_code& ec) noexcept
    {
        auto s = status(p, ec);

        if (!ec)
            return false;
        return is_other(s);
    }

    bool is_regular_file(file_status s) noexcept
    {
        return s.type() == file_type::regular;
    }

    bool is_regular_file(const path& p)
    {
        return is_regular_file(status(p));
    }

    bool is_regular_file(const path& p, error_code& ec) noexcept
    {
        auto s = status(p, ec);

        if (!ec)
            return false;
        return is_regular_file(s);
    }

    bool is_socket(file_status s) noexcept
    {
        return s.type() == file_type::socket;
    }

    bool is_socket(const path& p)
    {
        return is_socket(status(p));
    }

    bool is_socket(const path& p, error_code& ec) noexcept
    {
        auto s = status(p, ec);

        if (!ec)
            return false;
        return is_socket(s);
    }

    bool is_symlink(file_status s) noexcept
    {
        return s.type() == file_type::symlink;
    }

    bool is_symlink(const path& p)
    {
        return is_symlink(status(p));
    }

    bool is_symlink(const path& p, error_code& ec) noexcept
    {
        auto s = status(p, ec);

        if (!ec)
            return false;
        return is_symlink(s);
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
        return proximate(p, current_path(), ec);
    }

    path proximate(const path& p, const path& base)
    {
        return weakly_canonical(p).
            lexically_proximate(weakly_canonical(base));
    }

    path proximate(const path& p, const path& base, error_code& ec)
    {
        return weakly_canonical(p, ec).
            lexically_proximate(weakly_canonical(base, ec));
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
