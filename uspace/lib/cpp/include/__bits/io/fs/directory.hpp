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

namespace std::filesystem
{
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
}

#endif
