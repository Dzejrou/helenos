#
# Copyright (c) 2010 Martin Decky
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# - Redistributions of source code must retain the above copyright
#   notice, this list of conditions and the following disclaimer.
# - Redistributions in binary form must reproduce the above copyright
#   notice, this list of conditions and the following disclaimer in the
#   documentation and/or other materials provided with the distribution.
# - The name of the author may not be used to endorse or promote products
#   derived from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
# OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
# IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
# NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
# THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#


ifeq ($(COMPILER),gcc_cross)
	ifeq ($(CROSS_TARGET),arm32)
		ATSIGN = %
	endif

	ifeq ($(CROSS_TARGET),mips32)
		COMMON_CFLAGS += -mno-abicalls
	endif
endif

BITS = 32
ENDIANESS = LE

ARCH_SOURCES = \
	arch/$(KARCH)/src/debug/stacktrace.c \
	arch/$(KARCH)/src/proc/scheduler.c \
	arch/$(KARCH)/src/proc/task.c \
	arch/$(KARCH)/src/proc/thread.c \
	arch/$(KARCH)/src/abs32le.c \
	arch/$(KARCH)/src/userspace.c \
	arch/$(KARCH)/src/smc.c \
	arch/$(KARCH)/src/cpu/cpu.c \
	arch/$(KARCH)/src/smp/smp.c \
	arch/$(KARCH)/src/smp/ipi.c \
	arch/$(KARCH)/src/mm/km.c \
	arch/$(KARCH)/src/mm/as.c \
	arch/$(KARCH)/src/mm/frame.c \
	arch/$(KARCH)/src/mm/page.c \
	arch/$(KARCH)/src/mm/tlb.c
