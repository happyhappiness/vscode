static int parse_option(const char *arg, int len, unsigned int *colopts,
			int *group_set)
{
	struct colopt opts[] = {
		{ "always", COL_ENABLED,  COL_ENABLE_MASK },
		{ "never",  COL_DISABLED, COL_ENABLE_MASK },
		{ "auto",   COL_AUTO,     COL_ENABLE_MASK },
		{ "plain",  COL_PLAIN,    COL_LAYOUT_MASK },
		{ "column", COL_COLUMN,   COL_LAYOUT_MASK },
		{ "row",    COL_ROW,      COL_LAYOUT_MASK },
		{ "dense",  COL_DENSE,    0 },
	};
	int i;

	for (i = 0; i < ARRAY_SIZE(opts); i++) {
		int set = 1, arg_len = len, name_len;
		const char *arg_str = arg;

		if (!opts[i].mask) {
			if (arg_len > 2 && !strncmp(arg_str, "no", 2)) {
				arg_str += 2;
				arg_len -= 2;
				set = 0;
			}
		}

		name_len = strlen(opts[i].name);
		if (arg_len != name_len ||
		    strncmp(arg_str, opts[i].name, name_len))
			continue;

		switch (opts[i].mask) {
		case COL_ENABLE_MASK:
			*group_set |= ENABLE_SET;
			break;
		case COL_LAYOUT_MASK:
			*group_set |= LAYOUT_SET;
			break;
		}

		if (opts[i].mask)
			*colopts = (*colopts & ~opts[i].mask) | opts[i].value;
		else {
			if (set)
				*colopts |= opts[i].value;
			else
				*colopts &= ~opts[i].value;
		}
		return 0;
	}

	return error("unsupported option '%s'", arg);
}