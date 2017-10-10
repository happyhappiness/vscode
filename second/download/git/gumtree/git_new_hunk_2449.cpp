 *
 * Copyright (C) Linus Torvalds, 2005
 */
#include "git-compat-util.h"
#include "cache.h"

static FILE *error_handle;
static int tweaked_error_buffering;

void vreportf(const char *prefix, const char *err, va_list params)
{
	FILE *fh = error_handle ? error_handle : stderr;

	fflush(fh);
	if (!tweaked_error_buffering) {
		setvbuf(fh, NULL, _IOLBF, 0);
		tweaked_error_buffering = 1;
	}

	fputs(prefix, fh);
	vfprintf(fh, err, params);
	fputc('\n', fh);
}

static NORETURN void usage_builtin(const char *err, va_list params)
{
	vreportf("usage: ", err, params);
	exit(129);
