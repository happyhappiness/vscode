	return 0;
}

static int stdin_cacheinfo_callback(struct parse_opt_ctx_t *ctx,
			      const struct option *opt, int unset)
{
	int *line_termination = opt->value;

	if (ctx->argc != 1)
		return error("option '%s' must be the last argument", opt->long_name);
	allow_add = allow_replace = allow_remove = 1;
	read_index_info(*line_termination);
	return 0;
}

static int stdin_callback(struct parse_opt_ctx_t *ctx,
				const struct option *opt, int unset)
{
