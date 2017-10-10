	}
}

static void parse_options_check(const struct option *opts)
{
	int err = 0;

	for (; opts->type != OPTION_END; opts++) {
		if ((opts->flags & PARSE_OPT_LASTARG_DEFAULT) &&
		    (opts->flags & PARSE_OPT_OPTARG))
			err |= optbug(opts, "uses incompatible flags "
					"LASTARG_DEFAULT and OPTARG");
		if (opts->flags & PARSE_OPT_NODASH &&
		    ((opts->flags & PARSE_OPT_OPTARG) ||
		     !(opts->flags & PARSE_OPT_NOARG) ||
		     !(opts->flags & PARSE_OPT_NONEG) ||
		     opts->long_name))
			err |= optbug(opts, "uses feature "
