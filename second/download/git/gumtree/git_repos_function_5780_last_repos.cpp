int cmd_mktree(int ac, const char **av, const char *prefix)
{
	struct strbuf sb = STRBUF_INIT;
	unsigned char sha1[20];
	int nul_term_line = 0;
	int allow_missing = 0;
	int is_batch_mode = 0;
	int got_eof = 0;
	strbuf_getline_fn getline_fn;

	const struct option option[] = {
		OPT_BOOL('z', NULL, &nul_term_line, N_("input is NUL terminated")),
		OPT_SET_INT( 0 , "missing", &allow_missing, N_("allow missing objects"), 1),
		OPT_SET_INT( 0 , "batch", &is_batch_mode, N_("allow creation of more than one tree"), 1),
		OPT_END()
	};

	ac = parse_options(ac, av, prefix, option, mktree_usage, 0);
	getline_fn = nul_term_line ? strbuf_getline_nul : strbuf_getline_lf;

	while (!got_eof) {
		while (1) {
			if (getline_fn(&sb, stdin) == EOF) {
				got_eof = 1;
				break;
			}
			if (sb.buf[0] == '\0') {
				/* empty lines denote tree boundaries in batch mode */
				if (is_batch_mode)
					break;
				die("input format error: (blank line only valid in batch mode)");
			}
			mktree_line(sb.buf, sb.len, nul_term_line, allow_missing);
		}
		if (is_batch_mode && got_eof && used < 1) {
			/*
			 * Execution gets here if the last tree entry is terminated with a
			 * new-line.  The final new-line has been made optional to be
			 * consistent with the original non-batch behaviour of mktree.
			 */
			; /* skip creating an empty tree */
		} else {
			write_tree(sha1);
			puts(sha1_to_hex(sha1));
			fflush(stdout);
		}
		used=0; /* reset tree entry buffer for re-use in batch mode */
	}
	strbuf_release(&sb);
	exit(0);
}