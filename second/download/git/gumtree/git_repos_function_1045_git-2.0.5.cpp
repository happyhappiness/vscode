static int diff_scoreopt_parse(const char *opt)
{
	int opt1, opt2, cmd;

	if (*opt++ != '-')
		return -1;
	cmd = *opt++;
	if (cmd == '-') {
		/* convert the long-form arguments into short-form versions */
		if (starts_with(opt, "break-rewrites")) {
			opt += strlen("break-rewrites");
			if (*opt == 0 || *opt++ == '=')
				cmd = 'B';
		} else if (starts_with(opt, "find-copies")) {
			opt += strlen("find-copies");
			if (*opt == 0 || *opt++ == '=')
				cmd = 'C';
		} else if (starts_with(opt, "find-renames")) {
			opt += strlen("find-renames");
			if (*opt == 0 || *opt++ == '=')
				cmd = 'M';
		}
	}
	if (cmd != 'M' && cmd != 'C' && cmd != 'B')
		return -1; /* that is not a -M, -C, or -B option */

	opt1 = parse_rename_score(&opt);
	if (cmd != 'B')
		opt2 = 0;
	else {
		if (*opt == 0)
			opt2 = 0;
		else if (*opt != '/')
			return -1; /* we expect -B80/99 or -B80 */
		else {
			opt++;
			opt2 = parse_rename_score(&opt);
		}
	}
	if (*opt != 0)
		return -1;
	return opt1 | (opt2 << 16);
}