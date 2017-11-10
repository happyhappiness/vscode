static void pp_header(struct pretty_print_context *pp,
		      const char *encoding,
		      const struct commit *commit,
		      const char **msg_p,
		      struct strbuf *sb)
{
	int parents_shown = 0;

	for (;;) {
		const char *name, *line = *msg_p;
		int linelen = get_one_line(*msg_p);

		if (!linelen)
			return;
		*msg_p += linelen;

		if (linelen == 1)
			/* End of header */
			return;

		if (pp->fmt == CMIT_FMT_RAW) {
			strbuf_add(sb, line, linelen);
			continue;
		}

		if (starts_with(line, "parent ")) {
			if (linelen != 48)
				die("bad parent line in commit");
			continue;
		}

		if (!parents_shown) {
			unsigned num = commit_list_count(commit->parents);
			/* with enough slop */
			strbuf_grow(sb, num * 50 + 20);
			add_merge_info(pp, sb, commit);
			parents_shown = 1;
		}

		/*
		 * MEDIUM == DEFAULT shows only author with dates.
		 * FULL shows both authors but not dates.
		 * FULLER shows both authors and dates.
		 */
		if (skip_prefix(line, "author ", &name)) {
			strbuf_grow(sb, linelen + 80);
			pp_user_info(pp, "Author", sb, name, encoding);
		}
		if (skip_prefix(line, "committer ", &name) &&
		    (pp->fmt == CMIT_FMT_FULL || pp->fmt == CMIT_FMT_FULLER)) {
			strbuf_grow(sb, linelen + 80);
			pp_user_info(pp, "Commit", sb, name, encoding);
		}
	}
}