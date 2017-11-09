static int parse_nodash_opt(struct parse_opt_ctx_t *p, const char *arg,
			    const struct option *options)
{
	const struct option *all_opts = options;

	for (; options->type != OPTION_END; options++) {
		if (!(options->flags & PARSE_OPT_NODASH))
			continue;
		if (options->short_name == arg[0] && arg[1] == '\0')
			return get_value(p, options, all_opts, OPT_SHORT);
	}
	return -2;
}