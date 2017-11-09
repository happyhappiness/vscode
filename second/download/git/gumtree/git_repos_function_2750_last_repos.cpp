void parse_options_start(struct parse_opt_ctx_t *ctx,
			 int argc, const char **argv, const char *prefix,
			 const struct option *options, int flags)
{
	memset(ctx, 0, sizeof(*ctx));
	ctx->argc = ctx->total = argc - 1;
	ctx->argv = argv + 1;
	ctx->out  = argv;
	ctx->prefix = prefix;
	ctx->cpidx = ((flags & PARSE_OPT_KEEP_ARGV0) != 0);
	ctx->flags = flags;
	if ((flags & PARSE_OPT_KEEP_UNKNOWN) &&
	    (flags & PARSE_OPT_STOP_AT_NON_OPTION))
		die("STOP_AT_NON_OPTION and KEEP_UNKNOWN don't go together");
	parse_options_check(options);
}