static int parse_options_usage(struct parse_opt_ctx_t *ctx,
			       const char * const *usagestr,
			       const struct option *opts, int err)
{
	return usage_with_options_internal(ctx, usagestr, opts, 0, err);
}