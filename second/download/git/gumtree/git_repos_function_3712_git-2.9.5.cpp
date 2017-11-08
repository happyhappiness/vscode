static int grep_source_1(struct grep_opt *opt, struct grep_source *gs, int collect_hits)
{
	char *bol;
	char *peek_bol = NULL;
	unsigned long left;
	unsigned lno = 1;
	unsigned last_hit = 0;
	int binary_match_only = 0;
	unsigned count = 0;
	int try_lookahead = 0;
	int show_function = 0;
	struct userdiff_driver *textconv = NULL;
	enum grep_context ctx = GREP_CONTEXT_HEAD;
	xdemitconf_t xecfg;

	if (!opt->output)
		opt->output = std_output;

	if (opt->pre_context || opt->post_context || opt->file_break ||
	    opt->funcbody) {
		/* Show hunk marks, except for the first file. */
		if (opt->last_shown)
			opt->show_hunk_mark = 1;
		/*
		 * If we're using threads then we can't easily identify
		 * the first file.  Always put hunk marks in that case
		 * and skip the very first one later in work_done().
		 */
		if (opt->output != std_output)
			opt->show_hunk_mark = 1;
	}
	opt->last_shown = 0;

	if (opt->allow_textconv) {
		grep_source_load_driver(gs);
		/*
		 * We might set up the shared textconv cache data here, which
		 * is not thread-safe.
		 */
		grep_attr_lock();
		textconv = userdiff_get_textconv(gs->driver);
		grep_attr_unlock();
	}

	/*
	 * We know the result of a textconv is text, so we only have to care
	 * about binary handling if we are not using it.
	 */
	if (!textconv) {
		switch (opt->binary) {
		case GREP_BINARY_DEFAULT:
			if (grep_source_is_binary(gs))
				binary_match_only = 1;
			break;
		case GREP_BINARY_NOMATCH:
			if (grep_source_is_binary(gs))
				return 0; /* Assume unmatch */
			break;
		case GREP_BINARY_TEXT:
			break;
		default:
			die("bug: unknown binary handling mode");
		}
	}

	memset(&xecfg, 0, sizeof(xecfg));
	opt->priv = &xecfg;

	try_lookahead = should_lookahead(opt);

	if (fill_textconv_grep(textconv, gs) < 0)
		return 0;

	bol = gs->buf;
	left = gs->size;
	while (left) {
		char *eol, ch;
		int hit;

		/*
		 * look_ahead() skips quickly to the line that possibly
		 * has the next hit; don't call it if we need to do
		 * something more than just skipping the current line
		 * in response to an unmatch for the current line.  E.g.
		 * inside a post-context window, we will show the current
		 * line as a context around the previous hit when it
		 * doesn't hit.
		 */
		if (try_lookahead
		    && !(last_hit
			 && (show_function ||
			     lno <= last_hit + opt->post_context))
		    && look_ahead(opt, &left, &lno, &bol))
			break;
		eol = end_of_line(bol, &left);
		ch = *eol;
		*eol = 0;

		if ((ctx == GREP_CONTEXT_HEAD) && (eol == bol))
			ctx = GREP_CONTEXT_BODY;

		hit = match_line(opt, bol, eol, ctx, collect_hits);
		*eol = ch;

		if (collect_hits)
			goto next_line;

		/* "grep -v -e foo -e bla" should list lines
		 * that do not have either, so inversion should
		 * be done outside.
		 */
		if (opt->invert)
			hit = !hit;
		if (opt->unmatch_name_only) {
			if (hit)
				return 0;
			goto next_line;
		}
		if (hit) {
			count++;
			if (opt->status_only)
				return 1;
			if (opt->name_only) {
				show_name(opt, gs->name);
				return 1;
			}
			if (opt->count)
				goto next_line;
			if (binary_match_only) {
				opt->output(opt, "Binary file ", 12);
				output_color(opt, gs->name, strlen(gs->name),
					     opt->color_filename);
				opt->output(opt, " matches\n", 9);
				return 1;
			}
			/* Hit at this line.  If we haven't shown the
			 * pre-context lines, we would need to show them.
			 */
			if (opt->pre_context || opt->funcbody)
				show_pre_context(opt, gs, bol, eol, lno);
			else if (opt->funcname)
				show_funcname_line(opt, gs, bol, lno);
			show_line(opt, bol, eol, gs->name, lno, ':');
			last_hit = lno;
			if (opt->funcbody)
				show_function = 1;
			goto next_line;
		}
		if (show_function && (!peek_bol || peek_bol < bol)) {
			unsigned long peek_left = left;
			char *peek_eol = eol;

			/*
			 * Trailing empty lines are not interesting.
			 * Peek past them to see if they belong to the
			 * body of the current function.
			 */
			peek_bol = bol;
			while (is_empty_line(peek_bol, peek_eol)) {
				peek_bol = peek_eol + 1;
				peek_eol = end_of_line(peek_bol, &peek_left);
			}

			if (match_funcname(opt, gs, peek_bol, peek_eol))
				show_function = 0;
		}
		if (show_function ||
		    (last_hit && lno <= last_hit + opt->post_context)) {
			/* If the last hit is within the post context,
			 * we need to show this line.
			 */
			show_line(opt, bol, eol, gs->name, lno, '-');
		}

	next_line:
		bol = eol + 1;
		if (!left)
			break;
		left--;
		lno++;
	}

	if (collect_hits)
		return 0;

	if (opt->status_only)
		return 0;
	if (opt->unmatch_name_only) {
		/* We did not see any hit, so we want to show this */
		show_name(opt, gs->name);
		return 1;
	}

	xdiff_clear_find_func(&xecfg);
	opt->priv = NULL;

	/* NEEDSWORK:
	 * The real "grep -c foo *.c" gives many "bar.c:0" lines,
	 * which feels mostly useless but sometimes useful.  Maybe
	 * make it another option?  For now suppress them.
	 */
	if (opt->count && count) {
		char buf[32];
		if (opt->pathname) {
			output_color(opt, gs->name, strlen(gs->name),
				     opt->color_filename);
			output_sep(opt, ':');
		}
		snprintf(buf, sizeof(buf), "%u\n", count);
		opt->output(opt, buf, strlen(buf));
		return 1;
	}
	return !!last_hit;
}