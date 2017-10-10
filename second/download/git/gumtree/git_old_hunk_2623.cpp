			return -1;
		*(int *)opt->value = strtol(arg, (char **)&s, 10);
		if (*s)
			return opterror(opt, "expects a numerical value", flags);
		return 0;

	default:
		die("should not happen, someone must be hit on the forehead");
	}
}

static int parse_short_opt(struct parse_opt_ctx_t *p, const struct option *options)
