int parse_range_arg(const char *arg, nth_line_fn_t nth_line_cb,
		    void *cb_data, long lines, long anchor,
		    long *begin, long *end, const char *path)
{
	*begin = *end = 0;

	if (anchor < 1)
		anchor = 1;
	if (anchor > lines)
		anchor = lines + 1;

	if (*arg == ':' || (*arg == '^' && *(arg + 1) == ':')) {
		arg = parse_range_funcname(arg, nth_line_cb, cb_data, lines, anchor, begin, end, path);
		if (!arg || *arg)
			return -1;
		return 0;
	}

	arg = parse_loc(arg, nth_line_cb, cb_data, lines, -anchor, begin);

	if (*arg == ',')
		arg = parse_loc(arg + 1, nth_line_cb, cb_data, lines, *begin + 1, end);

	if (*arg)
		return -1;

	if (*begin && *end && *end < *begin) {
		SWAP(*end, *begin);
	}

	return 0;
}