/*
 * Copyright 2008 Peter Harris <git@peter.is-a-geek.org>
 */

#include "../git-compat-util.h"

/*
 Functions to be wrapped:
*/
#undef printf
#undef fprintf
#undef fputs
/* TODO: write */

/*
 ANSI codes used by git: m, K

 This file is git-specific. Therefore, this file does not attempt
 to implement any codes that are not used by git.
*/

static HANDLE console;
static WORD plain_attr;
static WORD attr;
static int negative;

static void init(void)
{
	CONSOLE_SCREEN_BUFFER_INFO sbi;

	static int initialized = 0;
	if (initialized)
		return;

	console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (console == INVALID_HANDLE_VALUE)
		console = NULL;

	if (!console)
		return;

	GetConsoleScreenBufferInfo(console, &sbi);
	attr = plain_attr = sbi.wAttributes;
	negative = 0;

	initialized = 1;
}


#define FOREGROUND_ALL (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
#define BACKGROUND_ALL (BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE)

static void set_console_attr(void)
{
