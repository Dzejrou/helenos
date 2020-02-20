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
{ // TODO: jzr made a commit fixing this
    typedef uint64_t aoff64_t;
    extern "C" {
        #include <vfs/vfs.h>
        #include <vfs/canonify.h>
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

    namespace aux
    {
        /**
         * This is an auxilliary status function that in
         * addition to the behaviour requested by
         * std::filesystem::status() also returns the HelenOS
         * specific stat structure to avoid redundant calls to
         * vfs_stat() when we need something besides the
         * type of a file.
         */
        file_status status(const path& p, error_code& ec,
                           helenos::vfs_stat_t& stat) noexcept
        {
            if (p.empty())
                return file_status{file_type::none};

            auto rc = helenos::vfs_stat_path(p.c_str(), &stat);
            if (rc != EOK)
            {
                LIBCPP_SET_ERRCODE(rc, ec);

                return file_status{file_type::not_found};
            }
            else
                ec.clear();

            file_type ftype{file_type::unknown};
            if (stat.is_file)
                ftype = file_type::regular;
            if (stat.is_directory)
                ftype = file_type::directory;

            return file_status{ftype};
        }
    }

    path absolute(const path& p)
    {
        return current_path() / p;
    }

    path absolute(const path& p, error_code&)
    {
        return current_path() / p;
    }

    path canonical(const path& p, const path& base)
    {
        error_code ec{};

        auto res = canonical(p, base, ec);
        if (ec.value() != EOK)
            LIBCPP_FSYSTEM_THROW(ec.value(), p);

        return res;
    }

    path canonical(const path& p, error_code& ec)
    {
        return canonical(p, current_path(), ec);
    }

    path canonical(const path& p, const path& base, error_code& ec)
    {
        auto full_path = p / base;
        size_t len{};

        auto* res_ptr = helenos::canonify(
            strndup(full_path.c_str(), full_path.native().size()), &len
        );
        if (!res_ptr)
        {
            LIBCPP_SET_ERRCODE(ENOENT, ec);

            return path{};
        }

        path res{string{res_ptr, len}};
        free(res_ptr);

        return res;
    }

    void copy(const path& from, const path& to)
    {
        copy(from, to, copy_options::none);
    }

    void copy(const path& from, const path& to, error_code& ec) noexcept
    {
        copy(from, to, copy_options::none, ec);
    }

    void copy(const path& from, const path& to, copy_options opts)
    {
        error_code ec{};

        copy(from, to, opts, ec);
        if (ec.value() != EOK)
            LIBCPP_FSYSTEM_THROW(ec.value(), from, to);
    }

    void copy(const path& from, const path& to,
              copy_options opts, error_code& ec) noexcept
    {
        // TODO:
        __unimplemented();
    }

    void copy_file(const path& from, const path& to)
    {
        copy_file(from, to, copy_options::none);
    }

    void copy_file(const path& from, const path& to, error_code& ec) noexcept
    {
        copy_file(from, to, copy_options::none, ec);
    }

    namespace aux
    {
        helenos::errno_t copy_file(const path& from, const path& to)
        {
            int f1{}, f2{};
            auto rc = helenos::vfs_lookup_open(
                from.c_str(), helenos::WALK_REGULAR,
                helenos::MODE_READ, &f1);
            if (rc != EOK)
                return rc;

            rc = helenos::vfs_lookup_open(
                to.c_str(), helenos::WALK_REGULAR | helenos::WALK_MAY_CREATE,
                helenos::MODE_WRITE, &f2);
            if (rc != EOK)
                return rc;

            size_t bsize = 4096;
            char buf[4096];
            helenos::aoff64_t rpos{}, wpos{};
            size_t nread{}, nwrite{};
            while (
                (rc = helenos::vfs_read(f1, &rpos, buf, bsize, &nread)) == EOK
                 && nread > 0
            )
            {
                if ((rc = helenos::vfs_write(f2, &wpos, buf, nread, &nwrite))
                    != EOK)
                    break;
            }

            return rc;
        }
    }

    void copy_file(const path& from, const path& to, copy_options opts)
    {
        error_code ec{};

        copy_file(from, to, opts, ec);
        if (ec.value() != EOK)
            LIBCPP_FSYSTEM_THROW(ec.value(), from, to);
    }

    void copy_file(const path& from, const path& to,
                   copy_options opts, error_code& ec) noexcept
    {
        bool existing_is_bad = (opts &
            (copy_options::skip_existing |
             copy_options::overwrite_existing |
             copy_options::update_existing)) == copy_options::none;

        auto exists_to = exists(to);
        if (!is_regular_file(from) || (exists_to && !is_regular_file(to)) ||
            (exists_to && equivalent(from, to)) ||
            (exists_to && existing_is_bad))
            LIBCPP_SET_ERRCODE(EEXIST, ec);

        auto overwrite = (opts & copy_options::overwrite_existing)
            != copy_options::none;
        auto update = (opts & copy_options::update_existing)
            != copy_options::none;
        bool from_more_recent_than_to = true; // No modify timestamp.

        if (!exists_to || overwrite || (update && from_more_recent_than_to))
        {
            auto rc = aux::copy_file(from, to);
            if (rc != EOK)
                LIBCPP_SET_ERRCODE(rc, ec);
        }
    }

    void copy_symlink(const path& from, const path& to)
    {
        error_code ec{};

        copy_symlink(from, to, ec);
        if (ec.value() != EOK)
            LIBCPP_FSYSTEM_THROW(ec.value(), from, to);
    }

    void copy_symlink(const path& from, const path& to, error_code& ec) noexcept
    {
        LIBCPP_SET_ERRCODE(ENOTSUP, ec);
    }

    bool create_directories(const path& p)
    {
        error_code ec{};

        auto res = create_directories(p, ec);
        if (ec.value() != EOK)
            LIBCPP_FSYSTEM_THROW(ec.value(), p);

        return res;
    }

    bool create_directories(const path& p, error_code& ec) noexcept
    {
        if (p.empty())
            return false;

        bool res{};
        const auto& native = p.native();

        size_t start{};
        if (native[0U] == path::preferred_separator)
            ++start;

        for (size_t idx = start; idx < native.size(); ++idx)
        {
            if (native[idx] == path::preferred_separator)
            {
                res = true;

                size_t size = (idx - start > 2U ? idx - start : 1U);
                auto rc = helenos::vfs_link_path(
                    native.substr(start, size).c_str(),
                    helenos::KIND_DIRECTORY, nullptr
                );
                if (rc != EOK)
                {
                    LIBCPP_SET_ERRCODE(rc, ec);

                    return false;
                }
            }
        }

        if (native[native.size() - 1] != '/')
        {
            auto rc = helenos::vfs_link_path(
                native.c_str(), helenos::KIND_DIRECTORY, nullptr
            );
            if (rc != EOK)
            {
                LIBCPP_SET_ERRCODE(rc, ec);

                return false;
            }
        }

        return res;
    }

    bool create_directory(const path& p)
    {
        error_code ec{};

        auto res = create_directory(p, ec);
        if (ec.value() != EOK)
            LIBCPP_FSYSTEM_THROW(ec.value(), p);

        return res;
    }

    bool create_directory(const path& p, error_code& ec)
    {
        auto rc = helenos::vfs_link_path(
            p.c_str(), helenos::KIND_DIRECTORY, nullptr
        );

        if (rc == EEXIST)
            return false;
        if (rc != EOK)
            LIBCPP_SET_ERRCODE(rc, ec);
        else
            ec.clear();

        return true;
    }

    bool create_directory(const path& p, const path& attrib)
    {
        error_code ec{};

        auto res = create_directory(p, attrib, ec);
        if (ec.value() != EOK)
            LIBCPP_FSYSTEM_THROW(ec.value(), p, attrib);

        return res;
    }

    bool create_directory(const path& p, const path& attrib,
                          error_code& ec) noexcept
    {
        /**
         * HelenOS does not have attributes that could be
         * copied from the second argument, but that is allowed
         * by the standard as all attributed are OS dependent.
         */
        return create_directory(p, ec);
    }

    void create_directory_symlink(const path& to, const path& new_symlink)
    {
        error_code ec{};

        create_directory_symlink(to, new_symlink, ec);
        if (ec.value() != EOK)
            LIBCPP_FSYSTEM_THROW(ec.value(), to, new_symlink);
    }

    void create_directory_symlink(const path& to, const path& new_symlink,
                                  error_code& ec) noexcept
    {
        LIBCPP_SET_ERRCODE(ENOTSUP, ec);
    }

    void create_hard_link(const path& to, const path& new_hard_link)
    {
        error_code ec{};

        create_hard_link(to, new_hard_link, ec);
        if (ec.value() != EOK)
            LIBCPP_FSYSTEM_THROW(ec.value(), to, new_hard_link);
    }

    void create_hard_link(const path& to, const path& new_hard_link,
                          error_code& ec) noexcept
    {
        LIBCPP_SET_ERRCODE(ENOTSUP, ec);
    }

    void create_symlink(const path& to, const path& new_symlink)
    {
        error_code ec{};

        create_symlink(to, new_symlink, ec);
        if (ec.value() != EOK)
            LIBCPP_FSYSTEM_THROW(ec.value(), to, new_symlink);
    }

    void create_symlink(const path& to, const path& new_symlink,
                        error_code& ec) noexcept
    {
        LIBCPP_SET_ERRCODE(ENOTSUP, ec);
    }

    path current_path()
    {
        error_code ec{};

        auto res = current_path(ec);
        if (ec.value() != EOK)
            LIBCPP_FSYSTEM_THROW(ec.value());

        return res;
    }

    path current_path(error_code& ec) noexcept
    {
        char buf[256];
        auto rc = helenos::vfs_cwd_get(buf, 256U);
        if (rc != EOK)
        {
            LIBCPP_SET_ERRCODE(rc, ec);
            return path{};
        }
        else
            ec.clear();

        return path{string{&buf[0]}};
    }

    void current_path(const path& p)
    {
        error_code ec{};

        current_path(p, ec);
        if (ec.value() != EOK)
            LIBCPP_FSYSTEM_THROW(ec.value(), p);
    }

    void current_path(const path& p, error_code& ec) noexcept
    {
        auto rc = helenos::vfs_cwd_set(p.c_str());
        if (rc != EOK)
            LIBCPP_SET_ERRCODE(rc, ec);
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
        error_code ec{};

        auto res = equivalent(p1, p2, ec);
        if (ec.value() != EOK)
            LIBCPP_FSYSTEM_THROW(ec.value(), p1, p2);

        return res;
    }

    bool equivalent(const path& p1, const path& p2, error_code& ec) noexcept
    {
        helenos::vfs_stat_t nstatus1{}, nstatus2{};
        error_code ec1{}, ec2{};

        auto s1 = aux::status(p1, ec1, nstatus1);
        if (!ec1)
            LIBCPP_SET_ERRCODE(ec1.value(), ec);

        auto s2 = aux::status(p2, ec2, nstatus2);
        if (!ec2)
            LIBCPP_SET_ERRCODE(ec2.value(), ec);

        if (!exists(s1) || !exists(s2) || (is_other(s1) && is_other(s2)))
            LIBCPP_SET_ERRCODE(ENOENT, ec);

        if (s1.type() != s2.type() || s1.permissions() != s2.permissions())
            return false;
        if (nstatus1.fs_handle != nstatus2.fs_handle ||
            nstatus1.index != nstatus2.index)
            return false;

        return true;
    }

    uintmax_t file_size(const path& p)
    {
        error_code ec{};

        auto res = file_size(p, ec);
        if (ec.value() != EOK)
            LIBCPP_FSYSTEM_THROW(ec.value(), p);

        return res;
    }

    uintmax_t file_size(const path& p, error_code& ec) noexcept
    {
        helenos::vfs_stat_t nstatus{};

        auto s = aux::status(p, ec, nstatus);
        if (!exists(s))
            LIBCPP_SET_ERRCODE(ENOENT, ec);
        if (ec.value() != EOK)
            return static_cast<uintmax_t>(-1);

        return static_cast<uintmax_t>(nstatus.size);
    }

    uintmax_t hard_link_count(const path& p)
    {
        error_code ec{};

        auto res = hard_link_count(p, ec);
        if (ec.value() != EOK)
            LIBCPP_FSYSTEM_THROW(ec.value(), p);

        return res;
    }

    uintmax_t hard_link_count(const path& p, error_code& ec) noexcept
    {
        LIBCPP_SET_ERRCODE(ENOTSUP, ec);

        return static_cast<uintmax_t>(-1);
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
        error_code ec{};

        auto res = is_empty(p, ec);
        if (ec.value() != EOK)
            LIBCPP_FSYSTEM_THROW(ec.value(), p);

        return res;
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
        error_code ec{};

        auto res = last_write_time(p, ec);
        if (ec.value() != EOK)
            LIBCPP_FSYSTEM_THROW(ec.value(), p);

        return res;
    }

    file_time_type last_write_time(const path& p, error_code& ec) noexcept
    {
        LIBCPP_SET_ERRCODE(ENOTSUP, ec);

        return file_time_type::min();
    }

    void last_write_time(const path& p, file_time_type new_time)
    {
        error_code ec{};

        last_write_time(p, new_time, ec);
        if (ec.value() != EOK)
            LIBCPP_FSYSTEM_THROW(ec.value(), p);
    }

    void last_write_time(const path& p, file_time_type new_time,
                         error_code& ec) noexcept
    {
        LIBCPP_SET_ERRCODE(ENOTSUP, ec);
    }

    void permissions(const path& p, perms prms,
                     perm_options opts)
    {
        error_code ec{};

        permissions(p, prms, opts, ec);
        if (ec.value() != EOK)
            LIBCPP_FSYSTEM_THROW(ec.value(), p);
    }

    void permissions(const path& p, perms prms, error_code& ec) noexcept
    {
        permissions(p, prms, perm_options::replace, ec);
    }

    void permissions(const path& p, perms prms, perm_options opts,
                     error_code& ec) noexcept
    {
        LIBCPP_SET_ERRCODE(ENOTSUP, ec);
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
        error_code ec{};

        auto res = read_symlink(p, ec);
        if (ec.value() != EOK)
            LIBCPP_FSYSTEM_THROW(ec.value());

        return res;
    }

    path read_symlink(const path& p, error_code& ec)
    {
        LIBCPP_SET_ERRCODE(ENOTSUP, ec);

        return path{};
    }

    path relative(const path& p, error_code& ec)
    {
        return relative(p, current_path(), ec);
    }

    path relative(const path& p, const path& base)
    {
        return weakly_canonical(p).
            lexically_relative(weakly_canonical(base));
    }

    path relative(const path& p, const path& base, error_code& ec)
    {
        return weakly_canonical(p, ec).
            lexically_relative(weakly_canonical(base, ec));
    }

    bool remove(const path& p)
    {
        error_code ec{};

        auto res = remove(p, ec);
        if (ec.value() != EOK)
            LIBCPP_FSYSTEM_THROW(ec.value(), p);

        return res;
    }

    bool remove(const path& p, error_code& ec) noexcept
    {
        auto rc = helenos::vfs_unlink_path(p.c_str());
        if (rc == ENOENT)
            return false;
        if (rc != EOK)
            LIBCPP_SET_ERRCODE(rc, ec);

        return true;
    }

    uintmax_t remove_all(const path& p)
    {
        error_code ec{};

        auto res = remove_all(p, ec);
        if (ec.value() != EOK)
            LIBCPP_FSYSTEM_THROW(ec.value(), p);

        return res;
    }

    uintmax_t remove_all(const path& p, error_code& ec) noexcept
    {
        // TODO:
        __unimplemented();

        return {};
    }

    void rename(const path& from, const path& to)
    {
        error_code ec{};

        rename(from, to, ec);
        if (ec.value() != EOK)
            LIBCPP_FSYSTEM_THROW(ec.value(), from, to);
    }

    void rename(const path& from, const path& to, error_code& ec) noexcept
    {
        if (from != to)
        {
            auto rc = helenos::vfs_rename_path(from.c_str(), to.c_str());
            if (rc != EOK)
                LIBCPP_SET_ERRCODE(rc, ec);
            else
                ec.clear();
        }
    }

    void resize_file(const path& p, uintmax_t size)
    {
        error_code ec{};

        resize_file(p, size, ec);
        if (ec.value() != EOK)
            LIBCPP_FSYSTEM_THROW(ec.value(), p);
    }

    void resize_file(const path& p, uintmax_t size, error_code& ec) noexcept
    {
        int handle{};
        auto rc = helenos::vfs_lookup(
            p.c_str(), helenos::WALK_REGULAR, &handle
        );
        if (rc != EOK)
        {
            LIBCPP_SET_ERRCODE(rc, ec);
            return;
        }
        else
            ec.clear();

        rc = helenos::vfs_resize(handle, (helenos::aoff64_t)size);
        if (rc != EOK)
            LIBCPP_SET_ERRCODE(rc, ec);
        else
            ec.clear();
    }

    space_info space(const path& p)
    {
        error_code ec{};

        auto res = space(p, ec);
        if (ec.value() != EOK)
            LIBCPP_FSYSTEM_THROW(ec.value(), p);

        return res;
    }

    space_info space(const path& p, error_code& ec)
    {
        helenos::vfs_statfs_t s{};

        auto rc = helenos::vfs_statfs_path(p.c_str(), &s);
        if (rc != EOK)
        {
            LIBCPP_SET_ERRCODE(rc, ec);

            return space_info{
                static_cast<uintmax_t>(-1),
                static_cast<uintmax_t>(-1),
                static_cast<uintmax_t>(-1)
            };
        }

        return space_info{
            s.f_blocks * s.f_bsize,
            s.f_bfree * s.f_bsize,
            (s.f_blocks * s.f_bsize) - (s.f_bfree * s.f_bsize)
        };
    }

    file_status status(const path& p)
    {
        error_code ec{};

        auto res = status(p, ec);
        if (res.type() == file_type::none)
            LIBCPP_FSYSTEM_THROW(ENOENT, p);
        if (ec.value() != EOK)
            LIBCPP_FSYSTEM_THROW(ec.value(), p);

        return res;
    }

    file_status status(const path& p, error_code& ec) noexcept
    {
        helenos::vfs_stat_t res{};

        return aux::status(p, ec, res);
    }

    bool status_known(file_status s) noexcept
    {
        return s.type() != file_type::none;
    }

    file_status symlink_status(const path& p)
    {
        error_code ec{};

        auto res = symlink_status(p, ec);
        if (ec.value() != EOK)
            LIBCPP_FSYSTEM_THROW(ec.value(), p);

        return res;
    }

    file_status symlink_status(const path& p, error_code& ec) noexcept
    {
        LIBCPP_SET_ERRCODE(ENOTSUP, ec);

        return file_status{file_type::unknown};
    }

    path temp_directory_path()
    {
        return path{string{"/tmp"}};
    }

    path temp_directory_path(error_code& ec) noexcept
    {
        return path{string{"/tmp"}};
    }

    path weakly_canonical(const path& p)
    {
        error_code ec{};

        auto res = weakly_canonical(p, ec);
        if (ec.value() != EOK)
            LIBCPP_FSYSTEM_THROW(ec.value(), p);

        return res;
    }

    path weakly_canonical(const path& p, error_code& ec)
    {
        // TODO:
        __unimplemented();

        return {};
    }
}
