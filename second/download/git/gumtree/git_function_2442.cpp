static void show_worktree(struct worktree *wt, int path_maxlen, int abbrev_len)
{
	struct strbuf sb = STRBUF_INIT;
	int cur_path_len = strlen(wt->path);
	int path_adj = cur_path_len - utf8_strwidth(wt->path);

	strbuf_addf(&sb, "%-*s ", 1 + path_maxlen + path_adj, wt->path);
	if (wt->is_bare)
		strbuf_addstr(&sb, "(bare)");
	else {
		strbuf_addf(&sb, "%-*s ", abbrev_len,
				find_unique_abbrev(wt->head_sha1, DEFAULT_ABBREV));
		if (!wt->is_detached)
			strbuf_addf(&sb, "[%s]", shorten_unambiguous_ref(wt->head_ref, 0));
		else
			strbuf_addstr(&sb, "(detached HEAD)");
	}
	printf("%s\n", sb.buf);

	strbuf_release(&sb);
}