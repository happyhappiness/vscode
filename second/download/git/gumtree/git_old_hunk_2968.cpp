		   const struct option *options)
{
	fprintf(stderr, "%s\n\n", msg);
	usage_with_options(usagestr, options);
}

static int parse_options_usage(struct parse_opt_ctx_t *ctx,
			       const char * const *usagestr,
			       const struct option *opts, int err)
{
	return usage_with_options_internal(ctx, usagestr, opts, 0, err);
}

#undef opterror
int opterror(const struct option *opt, const char *reason, int flags)
{
	if (flags & OPT_SHORT)
		return error("switch `%c' %s", opt->short_name, reason);
	if (flags & OPT_UNSET)
