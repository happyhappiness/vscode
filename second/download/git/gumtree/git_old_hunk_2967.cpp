#include "parse-options.h"
#include "cache.h"
#include "commit.h"
#include "color.h"
#include "utf8.h"

static int parse_options_usage(struct parse_opt_ctx_t *ctx,
			       const char * const *usagestr,
			       const struct option *opts, int err);

#define OPT_SHORT 1
#define OPT_UNSET 2

int optbug(const struct option *opt, const char *reason)
{
	if (opt->long_name) {
