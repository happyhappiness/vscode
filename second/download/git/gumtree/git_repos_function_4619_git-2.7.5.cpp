static int apply_one_fragment(struct image *img, struct fragment *frag,
			      int inaccurate_eof, unsigned ws_rule,
			      int nth_fragment)
{
	int match_beginning, match_end;
	const char *patch = frag->patch;
	int size = frag->size;
	char *old, *oldlines;
	struct strbuf newlines;
	int new_blank_lines_at_end = 0;
	int found_new_blank_lines_at_end = 0;
	int hunk_linenr = frag->linenr;
	unsigned long leading, trailing;
	int pos, applied_pos;
	struct image preimage;
	struct image postimage;

	memset(&preimage, 0, sizeof(preimage));
	memset(&postimage, 0, sizeof(postimage));
	oldlines = xmalloc(size);
	strbuf_init(&newlines, size);

	old = oldlines;
	while (size > 0) {
		char first;
		int len = linelen(patch, size);
		int plen;
		int added_blank_line = 0;
		int is_blank_context = 0;
		size_t start;

		if (!len)
			break;

		/*
		 * "plen" is how much of the line we should use for
		 * the actual patch data. Normally we just remove the
		 * first character on the line, but if the line is
		 * followed by "\ No newline", then we also remove the
		 * last one (which is the newline, of course).
		 */
		plen = len - 1;
		if (len < size && patch[len] == '\\')
			plen--;
		first = *patch;
		if (apply_in_reverse) {
			if (first == '-')
				first = '+';
			else if (first == '+')
				first = '-';
		}

		switch (first) {
		case '\n':
			/* Newer GNU diff, empty context line */
			if (plen < 0)
				/* ... followed by '\No newline'; nothing */
				break;
			*old++ = '\n';
			strbuf_addch(&newlines, '\n');
			add_line_info(&preimage, "\n", 1, LINE_COMMON);
			add_line_info(&postimage, "\n", 1, LINE_COMMON);
			is_blank_context = 1;
			break;
		case ' ':
			if (plen && (ws_rule & WS_BLANK_AT_EOF) &&
			    ws_blank_line(patch + 1, plen, ws_rule))
				is_blank_context = 1;
		case '-':
			memcpy(old, patch + 1, plen);
			add_line_info(&preimage, old, plen,
				      (first == ' ' ? LINE_COMMON : 0));
			old += plen;
			if (first == '-')
				break;
		/* Fall-through for ' ' */
		case '+':
			/* --no-add does not add new lines */
			if (first == '+' && no_add)
				break;

			start = newlines.len;
			if (first != '+' ||
			    !whitespace_error ||
			    ws_error_action != correct_ws_error) {
				strbuf_add(&newlines, patch + 1, plen);
			}
			else {
				ws_fix_copy(&newlines, patch + 1, plen, ws_rule, &applied_after_fixing_ws);
			}
			add_line_info(&postimage, newlines.buf + start, newlines.len - start,
				      (first == '+' ? 0 : LINE_COMMON));
			if (first == '+' &&
			    (ws_rule & WS_BLANK_AT_EOF) &&
			    ws_blank_line(patch + 1, plen, ws_rule))
				added_blank_line = 1;
			break;
		case '@': case '\\':
			/* Ignore it, we already handled it */
			break;
		default:
			if (apply_verbosely)
				error(_("invalid start of line: '%c'"), first);
			applied_pos = -1;
			goto out;
		}
		if (added_blank_line) {
			if (!new_blank_lines_at_end)
				found_new_blank_lines_at_end = hunk_linenr;
			new_blank_lines_at_end++;
		}
		else if (is_blank_context)
			;
		else
			new_blank_lines_at_end = 0;
		patch += len;
		size -= len;
		hunk_linenr++;
	}
	if (inaccurate_eof &&
	    old > oldlines && old[-1] == '\n' &&
	    newlines.len > 0 && newlines.buf[newlines.len - 1] == '\n') {
		old--;
		strbuf_setlen(&newlines, newlines.len - 1);
	}

	leading = frag->leading;
	trailing = frag->trailing;

	/*
	 * A hunk to change lines at the beginning would begin with
	 * @@ -1,L +N,M @@
	 * but we need to be careful.  -U0 that inserts before the second
	 * line also has this pattern.
	 *
	 * And a hunk to add to an empty file would begin with
	 * @@ -0,0 +N,M @@
	 *
	 * In other words, a hunk that is (frag->oldpos <= 1) with or
	 * without leading context must match at the beginning.
	 */
	match_beginning = (!frag->oldpos ||
			   (frag->oldpos == 1 && !unidiff_zero));

	/*
	 * A hunk without trailing lines must match at the end.
	 * However, we simply cannot tell if a hunk must match end
	 * from the lack of trailing lines if the patch was generated
	 * with unidiff without any context.
	 */
	match_end = !unidiff_zero && !trailing;

	pos = frag->newpos ? (