 *
 * Copyright (C) Linus Torvalds, 2005
 */
#include "git-compat-util.h"
#include "cache.h"

static FILE *error_handle;

void vreportf(const char *prefix, const char *err, va_list params)
{
	char msg[4096];
	FILE *fh = error_handle ? error_handle : stderr;
	char *p;

	vsnprintf(msg, sizeof(msg), err, params);
	for (p = msg; *p; p++) {
		if (iscntrl(*p) && *p != '\t' && *p != '\n')
			*p = '?';
	}
	fprintf(fh, "%s%s\n", prefix, msg);
}

static NORETURN void usage_builtin(const char *err, va_list params)
{
	vreportf("usage: ", err, params);
	exit(129);
