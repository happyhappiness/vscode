static int reupdate_callback(struct parse_opt_ctx_t *ctx,
				const struct option *opt, int flags)
{
	int *has_errors = opt->value;
	const char *prefix = startup_info->prefix;

	/* consume remaining arguments. */
	setup_work_tree();
	*has_errors = do_reupdate(ctx->argc, ctx->argv,
				prefix, prefix ? strlen(prefix) : 0);
	if (*has_errors)
		active_cache_changed = 0;

	ctx->argv += ctx->argc - 1;
	ctx->argc = 1;
	return 0;
}