static size_t format_commit_one(struct strbuf *sb, /* in UTF-8 */
				const char *placeholder,
				void *context)
{
	struct format_commit_context *c = context;
	const struct commit *commit = c->commit;
	const char *msg = c->message;
	struct commit_list *p;
	int h1, h2;

	/* these are independent of the commit */
	switch (placeholder[0]) {
	case 'C':
		if (starts_with(placeholder + 1, "(auto)")) {
			c->auto_color = want_color(c->pretty_ctx->color);
			return 7; /* consumed 7 bytes, "C(auto)" */
		} else {
			int ret = parse_color(sb, placeholder, c);
			if (ret)
				c->auto_color = 0;
			/*
			 * Otherwise, we decided to treat %C<unknown>
			 * as a literal string, and the previous
			 * %C(auto) is still valid.
			 */
			return ret;
		}
	case 'n':		/* newline */
		strbuf_addch(sb, '\n');
		return 1;
	case 'x':
		/* %x00 == NUL, %x0a == LF, etc. */
		if (0 <= (h1 = hexval_table[0xff & placeholder[1]]) &&
		    h1 <= 16 &&
		    0 <= (h2 = hexval_table[0xff & placeholder[2]]) &&
		    h2 <= 16) {
			strbuf_addch(sb, (h1<<4)|h2);
			return 3;
		} else
			return 0;
	case 'w':
		if (placeholder[1] == '(') {
			unsigned long width = 0, indent1 = 0, indent2 = 0;
			char *next;
			const char *start = placeholder + 2;
			const char *end = strchr(start, ')');
			if (!end)
				return 0;
			if (end > start) {
				width = strtoul(start, &next, 10);
				if (*next == ',') {
					indent1 = strtoul(next + 1, &next, 10);
					if (*next == ',') {
						indent2 = strtoul(next + 1,
								 &next, 10);
					}
				}
				if (*next != ')')
					return 0;
			}
			rewrap_message_tail(sb, c, width, indent1, indent2);
			return end - placeholder + 1;
		} else
			return 0;

	case '<':
	case '>':
		return parse_padding_placeholder(sb, placeholder, c);
	}

	/* these depend on the commit */
	if (!commit->object.parsed)
		parse_object(commit->object.oid.hash);

	switch (placeholder[0]) {
	case 'H':		/* commit hash */
		strbuf_addstr(sb, diff_get_color(c->auto_color, DIFF_COMMIT));
		strbuf_addstr(sb, oid_to_hex(&commit->object.oid));
		strbuf_addstr(sb, diff_get_color(c->auto_color, DIFF_RESET));
		return 1;
	case 'h':		/* abbreviated commit hash */
		strbuf_addstr(sb, diff_get_color(c->auto_color, DIFF_COMMIT));
		if (add_again(sb, &c->abbrev_commit_hash)) {
			strbuf_addstr(sb, diff_get_color(c->auto_color, DIFF_RESET));
			return 1;
		}
		strbuf_add_unique_abbrev(sb, commit->object.oid.hash,
					 c->pretty_ctx->abbrev);
		strbuf_addstr(sb, diff_get_color(c->auto_color, DIFF_RESET));
		c->abbrev_commit_hash.len = sb->len - c->abbrev_commit_hash.off;
		return 1;
	case 'T':		/* tree hash */
		strbuf_addstr(sb, oid_to_hex(&commit->tree->object.oid));
		return 1;
	case 't':		/* abbreviated tree hash */
		if (add_again(sb, &c->abbrev_tree_hash))
			return 1;
		strbuf_add_unique_abbrev(sb, commit->tree->object.oid.hash,
					 c->pretty_ctx->abbrev);
		c->abbrev_tree_hash.len = sb->len - c->abbrev_tree_hash.off;
		return 1;
	case 'P':		/* parent hashes */
		for (p = commit->parents; p; p = p->next) {
			if (p != commit->parents)
				strbuf_addch(sb, ' ');
			strbuf_addstr(sb, oid_to_hex(&p->item->object.oid));
		}
		return 1;
	case 'p':		/* abbreviated parent hashes */
		if (add_again(sb, &c->abbrev_parent_hashes))
			return 1;
		for (p = commit->parents; p; p = p->next) {
			if (p != commit->parents)
				strbuf_addch(sb, ' ');
			strbuf_add_unique_abbrev(sb, p->item->object.oid.hash,
						 c->pretty_ctx->abbrev);
		}
		c->abbrev_parent_hashes.len = sb->len -
		                              c->abbrev_parent_hashes.off;
		return 1;
	case 'm':		/* left/right/bottom */
		strbuf_addstr(sb, get_revision_mark(NULL, commit));
		return 1;
	case 'd':
		load_ref_decorations(DECORATE_SHORT_REFS);
		format_decorations(sb, commit, c->auto_color);
		return 1;
	case 'D':
		load_ref_decorations(DECORATE_SHORT_REFS);
		format_decorations_extended(sb, commit, c->auto_color, "", ", ", "");
		return 1;
	case 'g':		/* reflog info */
		switch(placeholder[1]) {
		case 'd':	/* reflog selector */
		case 'D':
			if (c->pretty_ctx->reflog_info)
				get_reflog_selector(sb,
						   