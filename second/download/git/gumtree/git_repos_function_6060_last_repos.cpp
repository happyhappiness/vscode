static int stdin_callback(struct parse_opt_ctx_t *ctx,
				const struct option *opt, int unset)
{
	int *read_from_stdin = opt->value;

	if (ctx->argc != 1)
		return error("option '%s' must be the last argument", opt->long_name);
	*read_from_stdin = 1;
	return 0;
}