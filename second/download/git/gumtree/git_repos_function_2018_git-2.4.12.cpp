int parse_options_step(struct parse_opt_ctx_t *ctx,
		       const struct option *options,
		       const char * const usagestr[])
{
	int internal_help = !(ctx->flags & PARSE_OPT_NO_INTERNAL_HELP);

	/* we must reset ->opt, unknown short option leave it dangling */
	ctx->opt = NULL;

	for (; ctx->argc; ctx->argc--, ctx->argv++) {
		const char *arg = ctx->argv[0];

		if (*arg != '-' || !arg[1]) {
			if (parse_nodash_opt(ctx, arg, options) == 0)
				continue;
			if (ctx->flags & PARSE_OPT_STOP_AT_NON_OPTION)
				return PARSE_OPT_NON_OPTION;
			ctx->out[ctx->cpidx++] = ctx->argv[0];
			continue;
		}

		if (arg[1] != '-') {
			ctx->opt = arg + 1;
			if (internal_help && *ctx->opt == 'h')
				return parse_options_usage(ctx, usagestr, options, 0);
			switch (parse_short_opt(ctx, options)) {
			case -1:
				return parse_options_usage(ctx, usagestr, options, 1);
			case -2:
				if (ctx->opt)
					check_typos(arg + 1, options);
				goto unknown;
			}
			if (ctx->opt)
				check_typos(arg + 1, options);
			while (ctx->opt) {
				if (internal_help && *ctx->opt == 'h')
					return parse_options_usage(ctx, usagestr, options, 0);
				switch (parse_short_opt(ctx, options)) {
				case -1:
					return parse_options_usage(ctx, usagestr, options, 1);
				case -2:
					/* fake a short option thing to hide the fact that we may have
					 * started to parse aggregated stuff
					 *
					 * This is leaky, too bad.
					 */
					ctx->argv[0] = xstrdup(ctx->opt - 1);
					*(char *)ctx->argv[0] = '-';
					goto unknown;
				}
			}
			continue;
		}

		if (!arg[2]) { /* "--" */
			if (!(ctx->flags & PARSE_OPT_KEEP_DASHDASH)) {
				ctx->argc--;
				ctx->argv++;
			}
			break;
		}

		if (internal_help && !strcmp(arg + 2, "help-all"))
			return usage_with_options_internal(ctx, usagestr, options, 1, 0);
		if (internal_help && !strcmp(arg + 2, "help"))
			return parse_options_usage(ctx, usagestr, options, 0);
		switch (parse_long_opt(ctx, arg + 2, options)) {
		case -1:
			return parse_options_usage(ctx, usagestr, options, 1);
		case -2:
			goto unknown;
		}
		continue;
unknown:
		if (!(ctx->flags & PARSE_OPT_KEEP_UNKNOWN))
			return PARSE_OPT_UNKNOWN;
		ctx->out[ctx->cpidx++] = ctx->argv[0];
		ctx->opt = NULL;
	}
	return PARSE_OPT_DONE;
}