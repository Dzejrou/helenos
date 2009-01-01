/*
 * Copyright (c) 2006 Ondrej Palkovsky
 * Copyright (c) 2008 Martin Decky
 * Copyright (c) 2008 Pavel Rimsky
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

/**
 * @defgroup serial Serial console
 * @brief    Serial console services (putc, puts, clear screen, cursor goto,...)
 * @{
 */ 

/** @file
 */

#include <stdio.h>
#include <ipc/ipc.h>
#include <async.h>
#include <ipc/fb.h>
#include <bool.h>
#include <errno.h>
#include <console/color.h>
#include <console/style.h>

#include "serial_console.h"

#define MAX_CONTROL 20

static void serial_sgr(const unsigned int mode);

static int width;
static int height;
static bool color = true;	/** True if producing color output. */
static putc_function_t putc_function;

/* Allow only 1 connection */
static int client_connected = 0;

enum sgr_color_index {
	CI_BLACK	= 0,
	CI_RED		= 1,
	CI_GREEN	= 2,
	CI_BROWN	= 3,
	CI_BLUE		= 4,
	CI_MAGENTA	= 5,
	CI_CYAN		= 6,
	CI_WHITE	= 7,
};

enum sgr_command {
	SGR_RESET	= 0,
	SGR_BOLD	= 1,
	SGR_BLINK	= 5,
	SGR_REVERSE	= 7,
	SGR_NORMAL_INT	= 22,
	SGR_BLINK_OFF	= 25,
	SGR_REVERSE_OFF = 27,
	SGR_FGCOLOR	= 30,
	SGR_BGCOLOR	= 40
};

static int color_map[] = {
	[COLOR_BLACK]	= CI_BLACK,
	[COLOR_BLUE]	= CI_RED,
	[COLOR_GREEN]	= CI_GREEN,
	[COLOR_CYAN]	= CI_CYAN,
	[COLOR_RED]	= CI_RED,
	[COLOR_MAGENTA] = CI_MAGENTA,
	[COLOR_YELLOW]	= CI_BROWN,
	[COLOR_WHITE]	= CI_WHITE
};

void serial_puts(char *str)
{
	while (*str)
		putc_function(*(str++));
}

void serial_goto(const unsigned int row, const unsigned int col)
{
	if ((row > height) || (col > width))
		return;
	
	char control[MAX_CONTROL];
	snprintf(control, MAX_CONTROL, "\033[%u;%uf", row + 1, col + 1);
	serial_puts(control);
}

void serial_clrscr(void)
{
	/* Initialize graphic rendition attributes. */
	serial_sgr(SGR_RESET);
	if (color) {
		serial_sgr(SGR_FGCOLOR + CI_BLACK);
		serial_sgr(SGR_BGCOLOR + CI_WHITE);
	}

	serial_puts("\033[2J");
}

void serial_scroll(int i)
{
	if (i > 0) {
		serial_goto(height - 1, 0);
		while (i--)
			serial_puts("\033D");
	} else if (i < 0) {
		serial_goto(0, 0);
		while (i++)
			serial_puts("\033M");
	}
}

/** ECMA-48 Set Graphics Rendition. */
static void serial_sgr(const unsigned int mode)
{
	char control[MAX_CONTROL];
	snprintf(control, MAX_CONTROL, "\033[%um", mode);
	serial_puts(control);
}

/** Set scrolling region. */
void serial_set_scroll_region(unsigned last_row)
{
	char control[MAX_CONTROL];
	snprintf(control, MAX_CONTROL, "\033[0;%ur", last_row);
	serial_puts(control);
}

void serial_cursor_disable(void)
{
	serial_puts("\033[?25l");
}

void serial_cursor_enable(void)
{
	serial_puts("\033[?25h");
}

void serial_console_init(putc_function_t putc_fn, uint32_t w, uint32_t h)
{
	width = w;
	height = h;
	putc_function = putc_fn;
}

/**
 * Main function of the thread serving client connections.
 */
void serial_client_connection(ipc_callid_t iid, ipc_call_t *icall)
{
	int retval;
	ipc_callid_t callid;
	ipc_call_t call;
	char c;
	int lastcol = 0;
	int lastrow = 0;
	int newcol;
	int newrow;
	int fgcolor;
	int bgcolor;
	int style;
	int i;
	
	if (client_connected) {
		ipc_answer_0(iid, ELIMIT);
		return;
	}
	
	client_connected = 1;
	ipc_answer_0(iid, EOK);
	
	/* Clear the terminal, set scrolling region
	   to 0 - height rows. */
	serial_clrscr();
	serial_goto(0, 0);
	serial_set_scroll_region(height);
	
	while (true) {
		callid = async_get_call(&call);
		switch (IPC_GET_METHOD(call)) {
		case IPC_M_PHONE_HUNGUP:
			client_connected = 0;
			ipc_answer_0(callid, EOK);
			return;
		case FB_PUTCHAR:
			c = IPC_GET_ARG1(call);
			newrow = IPC_GET_ARG2(call);
			newcol = IPC_GET_ARG3(call);
			if ((lastcol != newcol) || (lastrow != newrow))
				serial_goto(newrow, newcol);
			lastcol = newcol + 1;
			lastrow = newrow;
			(*putc_function)(c);
			retval = 0;
			break;
		case FB_CURSOR_GOTO:
			newrow = IPC_GET_ARG1(call);
			newcol = IPC_GET_ARG2(call);
			serial_goto(newrow, newcol);
			lastrow = newrow;
			lastcol = newcol;
			retval = 0;
			break;
		case FB_GET_CSIZE:
			ipc_answer_2(callid, EOK, height, width);
			continue;
		case FB_CLEAR:
			serial_clrscr();
			retval = 0;
			break;
		case FB_SET_STYLE:
			style =  IPC_GET_ARG1(call);
			if (style == STYLE_EMPHASIS) {
				if (color) {
					serial_sgr(SGR_RESET);
					serial_sgr(SGR_FGCOLOR + CI_RED);
					serial_sgr(SGR_BGCOLOR + CI_WHITE);
				}
				serial_sgr(SGR_BOLD);
			} else {
				if (color) {
					serial_sgr(SGR_RESET);
					serial_sgr(SGR_FGCOLOR + CI_BLACK);
					serial_sgr(SGR_BGCOLOR + CI_WHITE);
				}
				serial_sgr(SGR_NORMAL_INT);
			}
			retval = 0;
			break;
		case FB_SET_COLOR:
			fgcolor = IPC_GET_ARG1(call);
			bgcolor = IPC_GET_ARG2(call);

			if (color) {
				serial_sgr(SGR_RESET);
				serial_sgr(SGR_FGCOLOR + color_map[fgcolor]);
				serial_sgr(SGR_BGCOLOR + color_map[bgcolor]);
			} else {
				if (fgcolor < bgcolor)
					serial_sgr(SGR_RESET);
				else
					serial_sgr(SGR_REVERSE);
			}
			retval = 0;
			break;
		case FB_SET_RGB_COLOR:
			fgcolor = IPC_GET_ARG1(call);
			bgcolor = IPC_GET_ARG2(call);
			if (fgcolor < bgcolor)
				serial_sgr(SGR_REVERSE_OFF);
			else
				serial_sgr(SGR_REVERSE);
			retval = 0;
			break;
		case FB_SCROLL:
			i = IPC_GET_ARG1(call);
			if ((i > height) || (i < -height)) {
				retval = EINVAL;
				break;
			}
			serial_scroll(i);
			serial_goto(lastrow, lastcol);
			retval = 0;
			break;
		case FB_CURSOR_VISIBILITY:
			if(IPC_GET_ARG1(call))
				serial_cursor_enable();
			else
				serial_cursor_disable();
			retval = 0;
			break;
		default:
			retval = ENOENT;
		}
		ipc_answer_0(callid, retval);
	}
}

/** 
 * @}
 */
