int parse_options(int argc, const char **argv, const char *prefix,
		  const struct option *options, const char * const usagestr[],
		  int flags)
{
	struct parse_opt_ctx_t ctx;

	parse_options_start(&ctx, argc, argv, prefix, options, flags);
	switch (parse_options_step(&ctx, options, usagestr)) {
	case PARSE_OPT_HELP:
		exit(129);
	case PARSE_OPT_NON_OPTION:
	case PARSE_OPT_DONE:
		break;
	default: /* PARSE_OPT_UNKNOWN */
		if (ctx.argv[0][1] == '-') {
			error("unknown option `%s'", ctx.argv[0] + 2);
		} else if (isascii(*ctx.opt)) {
			error("unknown switch `%c'", *ctx.opt);
		} else {
			error("unknown non-ascii option in string: `%s'",
			      ctx.argv[0]);
		}
		usage_with_options(usagestr, options);
	}

	precompose_argv(argc, argv);
	return parse_options_end(&ctx);
}