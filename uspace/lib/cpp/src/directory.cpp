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

#include <__bits/io/fs/directory.hpp>
#include <__bits/utility/forward_move.hpp>
#include <__bits/trycatch.hpp>
#include <string>

namespace std::filesystem
{
    directory_entry::directory_entry(const aux::fs::path& p)
        : path_{p}
    {
        refresh();
    }

    directory_entry::directory_entry(const aux::fs::path& p, error_code& ec)
        : path_{p}
    {
        refresh(ec);
    }

    void directory_entry::assign(const aux::fs::path& p)
    {
        path_ = p;
        refresh();
    }

    void directory_entry::assign(const aux::fs::path& p, error_code& ec)
    {
        path_ = p;
        refresh(ec);
    }

    void directory_entry::replace_filename(const aux::fs::path& p)
    {
        path_.replace_filename(p);
        refresh();
    }

    void directory_entry::replace_filename(const aux::fs::path& p,
                                           error_code& ec)
    {
        path_.replace_filename(p);
        refresh(ec);
    }

    void directory_entry::refresh()
    {
        /**
         * Store cached attributes here in the future,
         * we don't cache at the moment.
         */
    }

    void directory_entry::refresh(error_code& ec) noexcept
    {
        /**
         * Store cached attributes here in the future,
         * we don't cache at the moment.
         */
    }

    const aux::fs::path& directory_entry::path() const noexcept
    {
        return path_;
    }

    directory_entry::operator const aux::fs::path&() const noexcept
    {
        return path_;
    }

    bool directory_entry::exists() const
    {
        return aux::fs::exists(this->status());
    }

    bool directory_entry::exists(error_code& ec) const noexcept\
    {
        return aux::fs::exists(this->status(ec));
    }

    bool directory_entry::is_block_file() const
    {
        return aux::fs::is_block_file(this->status());
    }

    bool directory_entry::is_block_file(error_code& ec) const noexcept\
    {
        return aux::fs::is_block_file(this->status(ec));
    }

    bool directory_entry::is_character_file() const
    {
        return aux::fs::is_character_file(this->status());
    }

    bool directory_entry::is_character_file(error_code& ec) const noexcept\
    {
        return aux::fs::is_character_file(this->status(ec));
    }

    bool directory_entry::is_directory() const
    {
        return aux::fs::is_directory(this->status());
    }

    bool directory_entry::is_directory(error_code& ec) const noexcept\
    {
        return aux::fs::is_directory(this->status(ec));
    }

    bool directory_entry::is_fifo() const
    {
        return aux::fs::is_fifo(this->status());
    }

    bool directory_entry::is_fifo(error_code& ec) const noexcept\
    {
        return aux::fs::is_fifo(this->status(ec));
    }

    bool directory_entry::is_other() const
    {
        return aux::fs::is_other(this->status());
    }

    bool directory_entry::is_other(error_code& ec) const noexcept\
    {
        return aux::fs::is_other(this->status(ec));
    }

    bool directory_entry::is_regular_file() const
    {
        return aux::fs::is_regular_file(this->status());
    }

    bool directory_entry::is_regular_file(error_code& ec) const noexcept\
    {
        return aux::fs::is_regular_file(this->status(ec));
    }

    bool directory_entry::is_socket() const
    {
        return aux::fs::is_socket(this->status());
    }

    bool directory_entry::is_socket(error_code& ec) const noexcept\
    {
        return aux::fs::is_socket(this->status(ec));
    }

    bool directory_entry::is_symlink() const
    {
        return aux::fs::is_symlink(this->status());
    }

    bool directory_entry::is_symlink(error_code& ec) const noexcept\
    {
        return aux::fs::is_symlink(this->status(ec));
    }

    uintmax_t directory_entry::file_size() const
    {
        // Return cached value when available.
        return aux::fs::file_size(path_);
    }

    uintmax_t directory_entry::file_size(error_code& ec) const noexcept
    {
        // Return cached value when available.
        return aux::fs::file_size(path_, ec);
    }

    uintmax_t directory_entry::hard_link_count() const
    {
        // Return cached value when available.
        return aux::fs::hard_link_count(path_);
    }

    uintmax_t directory_entry::hard_link_count(error_code& ec) const noexcept
    {
        // Return cached value when available.
        return aux::fs::hard_link_count(path_, ec);
    }

    file_time_type directory_entry::last_write_time() const
    {
        // Return cached value when available.
        return aux::fs::last_write_time(path_);
    }

    file_time_type directory_entry::last_write_time(error_code& ec) const noexcept
    {
        // Return cached value when available.
        return aux::fs::last_write_time(path_, ec);
    }

    file_status directory_entry::status() const
    {
        // Return cached value when available.
        return aux::fs::status(path_);
    }

    file_status directory_entry::status(error_code& ec) const noexcept
    {
        // Return cached value when available.
        return aux::fs::status(path_, ec);
    }

    file_status directory_entry::symlink_status() const
    {
        // Return cached value when available.
        return aux::fs::symlink_status(path_);
    }

    file_status directory_entry::symlink_status(error_code& ec) const noexcept
    {
        // Return cached value when available.
        return aux::fs::symlink_status(path_, ec);
    }

    bool directory_entry::operator<(const directory_entry& rhs) const noexcept
    {
        return path_ < rhs.path_;
    }

    bool directory_entry::operator==(const directory_entry& rhs) const noexcept
    {
        return path_ == rhs.path_;
    }

    bool directory_entry::operator!=(const directory_entry& rhs) const noexcept
    {
        return path_ != rhs.path_;
    }

    bool directory_entry::operator<=(const directory_entry& rhs) const noexcept
    {
        return path_ <= rhs.path_;
    }

    bool directory_entry::operator>(const directory_entry& rhs) const noexcept
    {
        return path_ > rhs.path_;
    }

    bool directory_entry::operator>=(const directory_entry& rhs) const noexcept
    {
        return path_ >= rhs.path_;
    }

    directory_iterator::directory_iterator() noexcept
        : dir_{}, curr_{}
    { /* DUMMY BODY */ }

    directory_iterator::directory_iterator(const path& p)
        : dir_{}, curr_{}, dir_path_{p}
    {
        dir_ = opendir(p.string().c_str());
        if (!dir_)
            LIBCPP_FSYSTEM_THROW(errno, p);

        auto* curr_dirent = readdir(dir_);
        if (!curr_dirent)
        {
            if (errno == ENOENT)
            {
                *this = directory_iterator{};

                return;
            }

            LIBCPP_FSYSTEM_THROW(errno, p);
        }

        curr_ = directory_entry{
            dir_path_ / path{string{&curr_dirent->d_name[0]}}
        };
    }

    directory_iterator::directory_iterator(const path& p,
                                           directory_options opts)
        : directory_iterator{p}
    {
        /**
         * HelenOS does not seem to support permissions and
         * symlinks, so we're ignoring directory options as those
         * are the only two directory options supported by C++.
         */
    }

    directory_iterator::directory_iterator(const path& p, error_code& ec)
        noexcept
        : dir_{}, curr_{}, dir_path_{p}
    {
        dir_ = opendir(p.string().c_str());
        if (!dir_)
        {
            LIBCPP_SET_ERRCODE(errno, ec);

            return;
        }

        auto* curr_dirent = readdir(dir_);
        if (!curr_dirent)
        {
            if (ec.value() == EOK)
            { // Empty directory.
                *this = directory_iterator{};

                return;
            }
            LIBCPP_SET_ERRCODE(errno, ec);

            return;
        }

        curr_ = directory_entry{
            dir_path_ / path{string{&curr_dirent->d_name[0]}}, ec
        };
    }

    directory_iterator::directory_iterator(const path& p,
                                           directory_options opts,
                                           error_code& ec) noexcept
        : directory_iterator{p, ec}
    {
        /**
         * HelenOS does not seem to support permissions and
         * symlinks, so we're ignoring directory options as those
         * are the only two directory options supported by C++.
         */
    }

    directory_iterator::directory_iterator(const directory_iterator& rhs)
        : dir_{}, curr_{rhs.curr_}, dir_path_{rhs.dir_path_}
    {
        if (!rhs.dir_)
            dir_ = nullptr;
        else
        {
            dir_ = rhs.dir_;
            curr_ = rhs.curr_;

            rhs.dir_ = nullptr;
        }
    }

    directory_iterator::directory_iterator(directory_iterator&& rhs) noexcept
        : dir_{rhs.dir_}, curr_{move(rhs.curr_)}, dir_path_{move(rhs.dir_path_)}
    {
        rhs.dir_ = nullptr;
        rhs.curr_ = directory_entry{};
    }

    directory_iterator::~directory_iterator()
    {
        if (dir_)
            closedir(dir_);
    }

    directory_iterator& directory_iterator::operator=(const directory_iterator& rhs)
    {
        if (this == &rhs)
            return *this;

        if (dir_)
            closedir(dir_);
        if (!rhs.dir_)
            dir_ = nullptr;
        else
        {
            dir_ = rhs.dir_;
            curr_ = rhs.curr_;
            dir_path_ = rhs.dir_path_;

            rhs.dir_ = nullptr;
        }

        return *this;
    }

    directory_iterator& directory_iterator::operator=(directory_iterator&& rhs) noexcept
    {
        if (this == &rhs)
            return *this;

        dir_ = rhs.dir_;
        curr_ = move(rhs.curr_);
        dir_path_ = move(rhs.dir_path_);

        rhs.dir_ = nullptr;
        rhs.curr_ = directory_entry{};

        return *this;
    }

    auto directory_iterator::operator*() const -> reference
    {
        return curr_;
    }

    auto directory_iterator::operator->() const -> pointer
    {
        return &curr_;
    }

    directory_iterator directory_iterator::operator++(int)
    {
        auto tmp = *this;
        ++(*this);

        return tmp;
    }

    directory_iterator& directory_iterator::operator++()
    {
        if (dir_)
        {
            auto entry = readdir(dir_);
            if (!entry)
            {
                if (errno != ENOENT)
                    LIBCPP_FSYSTEM_THROW(errno);
                else
                {
                    // Change to end iterator.
                    closedir(dir_);
                    dir_ = nullptr;
                    curr_ = directory_entry{};

                    return *this;
                }
            }

            curr_ = directory_entry{
                dir_path_ / path{string{&entry->d_name[0]}}
            };
        }

        return *this;
    }

    directory_iterator& directory_iterator::increment(error_code& ec) noexcept
    {
        if (dir_)
        {
            auto entry = readdir(dir_);
            if (!entry)
            {
                if (errno != ENOENT)
                    LIBCPP_SET_ERRCODE(errno, ec);
                else
                {
                    // Change to end iterator.
                    closedir(dir_);
                    dir_ = nullptr;
                    curr_ = directory_entry{};

                    return *this;
                }
            }

            curr_ = directory_entry{
                dir_path_ / path{string{&entry->d_name[0]}}, ec
            };
        }

        return *this;
    }

    bool directory_iterator::operator==(const directory_iterator& rhs) const noexcept
    {
        return !(*this != rhs);
    }

    bool directory_iterator::operator!=(const directory_iterator& rhs) const noexcept
    {
        if (!dir_ && !rhs.dir_)
            return false; // Two end iterators.
        if (!dir_ || !rhs.dir_)
            return true; // End never equals to anything but another end.
        return curr_ != rhs.curr_;
    }

    directory_iterator begin(directory_iterator it) noexcept
    {
        return it;
    }

    directory_iterator end(const directory_iterator&) noexcept
    {
        return directory_iterator{};
    }

    recursive_directory_iterator::recursive_directory_iterator() noexcept
        : opts_{directory_options::none}, rec_pending_{false}, dir_{}, curr_{}
    { /* DUMMY BODY */ }

    recursive_directory_iterator::recursive_directory_iterator(const path& p)
        : recursive_directory_iterator{p, directory_options::none}
    { /* DUMMY BODY */ }

    recursive_directory_iterator::recursive_directory_iterator(
        const path& p, directory_options opts)
        : opts_{opts}, rec_pending_{true}, dir_{}, curr_{}
    {
        dir_ = opendir(p.string().c_str());
        if (!dir_)
            LIBCPP_FSYSTEM_THROW(errno, p);

        // TODO: errno EOK when the dir is empty?
        auto* curr_dirent = readdir(dir_);
        if (!curr_dirent)
            LIBCPP_FSYSTEM_THROW(errno, p);

        curr_ = directory_entry{
            path{string{&curr_dirent->d_name[0]}}
        };
    }

    recursive_directory_iterator::recursive_directory_iterator(
        const path& p, directory_options opts, error_code& ec) noexcept
        : opts_{opts}, rec_pending_{true}, dir_{}, curr_{}
    {
        dir_ = opendir(p.string().c_str());
        if (!dir_)
        {
            LIBCPP_SET_ERRCODE(errno, ec);

            return;
        }

        // TODO: errno EOK when the dir is empty?
        auto* curr_dirent = readdir(dir_);
        if (!curr_dirent)
        {
            LIBCPP_SET_ERRCODE(errno, ec);

            return;
        }

        curr_ = directory_entry{
            path{string{&curr_dirent->d_name[0]}}, ec
        };
    }

    recursive_directory_iterator::recursive_directory_iterator(
        const path& p, error_code& ec) noexcept
        : recursive_directory_iterator{p, directory_options::none, ec}
    { /* DUMMY BODY */ }

    recursive_directory_iterator::recursive_directory_iterator(
        const recursive_directory_iterator& rhs)
        : opts_{rhs.opts_}, rec_pending_{rhs.rec_pending_},
          dir_{rhs.dir_}, curr_{rhs.curr_}, dir_stack_{rhs.dir_stack_}
    {
        rhs.dir_ = nullptr; // To avoid double free, rhs is invalid.
    }

    recursive_directory_iterator::recursive_directory_iterator(
        recursive_directory_iterator&& rhs) noexcept
        : opts_{rhs.opts_}, rec_pending_{rhs.rec_pending_},
          dir_{rhs.dir_}, curr_{move(rhs.curr_)},
          dir_stack_{move(rhs.dir_stack_)}
    {
        rhs.dir_ = nullptr;
    }

    recursive_directory_iterator::~recursive_directory_iterator()
    {
        if (dir_)
            closedir(dir_);

        while (dir_stack_.size() > 0U)
        {
            closedir(dir_stack_.top());
            dir_stack_.pop();
        }
    }

    recursive_directory_iterator&
    recursive_directory_iterator::operator=(
        const recursive_directory_iterator& rhs)
    {
        opts_ = rhs.opts_;
        rec_pending_ = rhs.rec_pending_;
        dir_ = rhs.dir_;
        curr_ = rhs.curr_;
        dir_stack_ = rhs.dir_stack_;

        rhs.dir_ = nullptr; // To avoid double free, rhs is invalid.

        return *this;
    }

    recursive_directory_iterator&
    recursive_directory_iterator::operator=(
        recursive_directory_iterator&& rhs) noexcept
    {
        opts_ = rhs.opts_;
        rec_pending_ = rhs.rec_pending_;
        dir_ = rhs.dir_;
        curr_ = move(rhs.curr_);
        dir_stack_ = move(rhs.dir_stack_);

        rhs.dir_ = nullptr;

        return *this;
    }

    directory_options recursive_directory_iterator::options() const
    {
        return opts_;
    }

    int recursive_directory_iterator::depth() const
    {
        return const_cast<recursive_directory_iterator&>(*this)
            .dir_stack_.size();
    }

    bool recursive_directory_iterator::recursion_pending() const
    {
        return rec_pending_;
    }

    auto recursive_directory_iterator::operator*() const -> reference
    {
        return curr_;
    }

    auto recursive_directory_iterator::operator->() const -> pointer
    {
        return &curr_;
    }

    recursive_directory_iterator recursive_directory_iterator::operator++(int)
    {
        auto tmp = *this;
        ++(*this);

        return tmp;
    }

    recursive_directory_iterator& recursive_directory_iterator::operator++()
    {
        auto rc = increment_();
        if (rc != EOK)
            LIBCPP_FSYSTEM_THROW(rc, curr_);

        return *this;
    }

    recursive_directory_iterator&
    recursive_directory_iterator::increment(error_code& ec) noexcept
    {
        auto rc = increment_();
        if (rc != EOK)
            LIBCPP_SET_ERRCODE(rc, ec);

        return *this;
    }

    bool recursive_directory_iterator::operator!=(
        const recursive_directory_iterator& rhs) const noexcept
    {
        if (!dir_ && !rhs.dir_)
            return false; // Two end iterators.
        if (!dir_ || !rhs.dir_)
            return true; // End never equals to anything but another end.
        return curr_ != rhs.curr_;
    }

    void recursive_directory_iterator::pop()
    {
        if (dir_)
            closedir(dir_);

        if (dir_stack_.size() > 0U)
        {
            dir_ = dir_stack_.top();
            dir_stack_.pop();

            // Read the next uncle.
            auto* curr_dirent = readdir(dir_);
            if (!curr_dirent)
            {
                if (errno == ENOENT)
                { // This directory is the last in its parent.
                    pop();

                    return;
                }

                LIBCPP_FSYSTEM_THROW(errno);
            }

            curr_ = directory_entry{
                path{string{&curr_dirent->d_name[0]}}
            };
        }
        else
            *this = recursive_directory_iterator{};
    }

    void recursive_directory_iterator::pop(error_code& ec) noexcept
    {
        if (dir_)
            closedir(dir_);

        if (dir_stack_.size() > 0U)
        {
            dir_ = dir_stack_.top();
            dir_stack_.pop();

            // Read the next uncle.
            auto* curr_dirent = readdir(dir_);
            if (!curr_dirent)
            {
                if (errno == ENOENT)
                { // This directory is the last in its parent.
                    pop(ec);

                    return;
                }

                LIBCPP_SET_ERRCODE(errno, ec);

                return;
            }

            curr_ = directory_entry{
                path{string{&curr_dirent->d_name[0]}}, ec
            };
        }
        else
            *this = recursive_directory_iterator{};
    }

    void recursive_directory_iterator::disable_recursion_pending()
    {
        rec_pending_ = false;
    }

    bool recursive_directory_iterator::should_enter_subdir_() const
    {
        if (rec_pending_ && is_directory(curr_.status()))
            return true;

        /**
         * Here should also be check if curr_ is a symlink and
         * opts_ does contain follow_directory_symlink.
         */

        return false;
    }

    int recursive_directory_iterator::increment_()
    {
        if (dir_)
        {
            auto entry = readdir(dir_);
            if (!entry)
            {
                if (errno != ENOENT)
                    return errno;
                if (dir_stack_.size() > 0U)
                    pop();
                else
                {
                    // Change to end iterator.
                    closedir(dir_);
                    dir_ = nullptr;
                    curr_ = directory_entry{};
                }

                return EOK;
            }

            curr_ = directory_entry{
                path{string{&entry->d_name[0]}}
            };

            if (should_enter_subdir_())
            {
                dir_stack_.push(dir_);
                dir_ = opendir(curr_.path().c_str());
                if (!dir_)
                    return errno;

                auto entry = readdir(dir_);
                if (!entry)
                {
                    if (errno != ENOENT)
                        return errno;
                    pop();

                    return EOK;
                }

                curr_ = directory_entry{
                    path{string{&entry->d_name[0]}}
                };
            }

            rec_pending_ = true;
        }

        return EOK;
    }

    recursive_directory_iterator
    begin(recursive_directory_iterator it) noexcept
    {
        return it;
    }

    recursive_directory_iterator
    end(const recursive_directory_iterator&) noexcept
    {
        return recursive_directory_iterator{};
    }
}