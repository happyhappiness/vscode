static int get_value(struct parse_opt_ctx_t *p,
		     const struct option *opt,
		     const struct option *all_opts,
		     int flags)
{
	const char *s, *arg;
	const int unset = flags & OPT_UNSET;
	int err;

	if (unset && p->opt)
		return opterror(opt, "takes no value", flags);
	if (unset && (opt->flags & PARSE_OPT_NONEG))
		return opterror(opt, "isn't available", flags);
	if (!(flags & OPT_SHORT) && p->opt && (opt->flags & PARSE_OPT_NOARG))
		return opterror(opt, "takes no value", flags);

	switch (opt->type) {
	case OPTION_LOWLEVEL_CALLBACK:
		return (*(parse_opt_ll_cb *)opt->callback)(p, opt, unset);

	case OPTION_BIT:
		if (unset)
			*(int *)opt->value &= ~opt->defval;
		else
			*(int *)opt->value |= opt->defval;
		return 0;

	case OPTION_NEGBIT:
		if (unset)
			*(int *)opt->value |= opt->defval;
		else
			*(int *)opt->value &= ~opt->defval;
		return 0;

	case OPTION_COUNTUP:
		*(int *)opt->value = unset ? 0 : *(int *)opt->value + 1;
		return 0;

	case OPTION_SET_INT:
		*(int *)opt->value = unset ? 0 : opt->defval;
		return 0;

	case OPTION_CMDMODE:
		/*
		 * Giving the same mode option twice, although is unnecessary,
		 * is not a grave error, so let it pass.
		 */
		if (*(int *)opt->value && *(int *)opt->value != opt->defval)
			return opt_command_mode_error(opt, all_opts, flags);
		*(int *)opt->value = opt->defval;
		return 0;

	case OPTION_STRING:
		if (unset)
			*(const char **)opt->value = NULL;
		else if (opt->flags & PARSE_OPT_OPTARG && !p->opt)
			*(const char **)opt->value = (const char *)opt->defval;
		else
			return get_arg(p, opt, flags, (const char **)opt->value);
		return 0;

	case OPTION_FILENAME:
		err = 0;
		if (unset)
			*(const char **)opt->value = NULL;
		else if (opt->flags & PARSE_OPT_OPTARG && !p->opt)
			*(const char **)opt->value = (const char *)opt->defval;
		else
			err = get_arg(p, opt, flags, (const char **)opt->value);

		if (!err)
			fix_filename(p->prefix, (const char **)opt->value);
		return err;

	case OPTION_CALLBACK:
		if (unset)
			return (*opt->callback)(opt, NULL, 1) ? (-1) : 0;
		if (opt->flags & PARSE_OPT_NOARG)
			return (*opt->callback)(opt, NULL, 0) ? (-1) : 0;
		if (opt->flags & PARSE_OPT_OPTARG && !p->opt)
			return (*opt->callback)(opt, NULL, 0) ? (-1) : 0;
		if (get_arg(p, opt, flags, &arg))
			return -1;
		return (*opt->callback)(opt, arg, 0) ? (-1) : 0;

	case OPTION_INTEGER:
		if (unset) {
			*(int *)opt->value = 0;
			return 0;
		}
		if (opt->flags & PARSE_OPT_OPTARG && !p->opt) {
			*(int *)opt->value = opt->defval;
			return 0;
		}
		if (get_arg(p, opt, flags, &arg))
			return -1;
		*(int *)opt->value = strtol(arg, (char **)&s, 10);
		if (*s)
			return opterror(opt, "expects a numerical value", flags);
		return 0;

	case OPTION_MAGNITUDE:
		if (unset) {
			*(unsigned long *)opt->value = 0;
			return 0;
		}
		if (opt->flags & PARSE_OPT_OPTARG && !p->opt) {
			*(unsigned long *)opt->value = opt->defval;
			return 0;
		}
		if (get_arg(p, opt, flags, &arg))
			return -1;
		if (!git_parse_ulong(arg, opt->value))
			return opterror(opt,
				"expects a non-negative integer value with an optional k/m/g suffix",
				flags);
		return 0;

	default:
		die("should not happen, someone must be hit on the forehead");
	}
}