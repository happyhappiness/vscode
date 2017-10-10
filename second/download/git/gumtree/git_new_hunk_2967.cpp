#include "parse-options.h"
#include "cache.h"
#include "commit.h"
#include "color.h"
#include "utf8.h"

#define OPT_SHORT 1
#define OPT_UNSET 2

int optbug(const struct option *opt, const char *reason)
{
	if (opt->long_name) {
