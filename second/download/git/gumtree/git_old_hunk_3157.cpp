}

int cmd_mktree(int ac, const char **av, const char *prefix)
{
	struct strbuf sb = STRBUF_INIT;
	unsigned char sha1[20];
	int line_termination = '\n';
	int allow_missing = 0;
	int is_batch_mode = 0;
	int got_eof = 0;

	const struct option option[] = {
		OPT_SET_INT('z', NULL, &line_termination, N_("input is NUL terminated"), '\0'),
		OPT_SET_INT( 0 , "missing", &allow_missing, N_("allow missing objects"), 1),
		OPT_SET_INT( 0 , "batch", &is_batch_mode, N_("allow creation of more than one tree"), 1),
		OPT_END()
	};

	ac = parse_options(ac, av, prefix, option, mktree_usage, 0);

	while (!got_eof) {
		while (1) {
			if (strbuf_getline(&sb, stdin, line_termination) == EOF) {
				got_eof = 1;
				break;
			}
			if (sb.buf[0] == '\0') {
				/* empty lines denote tree boundaries in batch mode */
				if (is_batch_mode)
					break;
				die("input format error: (blank line only valid in batch mode)");
			}
			mktree_line(sb.buf, sb.len, line_termination, allow_missing);
		}
		if (is_batch_mode && got_eof && used < 1) {
			/*
			 * Execution gets here if the last tree entry is terminated with a
			 * new-line.  The final new-line has been made optional to be
			 * consistent with the original non-batch behaviour of mktree.
