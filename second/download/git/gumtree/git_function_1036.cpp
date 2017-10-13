static int prepare_include_condition_pattern(struct strbuf *pat)
{
	struct strbuf path = STRBUF_INIT;
	char *expanded;
	int prefix = 0;

	expanded = expand_user_path(pat->buf, 1);
	if (expanded) {
		strbuf_reset(pat);
		strbuf_addstr(pat, expanded);
		free(expanded);
	}

	if (pat->buf[0] == '.' && is_dir_sep(pat->buf[1])) {
		const char *slash;

		if (!cf || !cf->path)
			return error(_("relative config include "
				       "conditionals must come from files"));

		strbuf_realpath(&path, cf->path, 1);
		slash = find_last_dir_sep(path.buf);
		if (!slash)
			die("BUG: how is this possible?");
		strbuf_splice(pat, 0, 1, path.buf, slash - path.buf);
		prefix = slash - path.buf + 1 /* slash */;
	} else if (!is_absolute_path(pat->buf))
		strbuf_insert(pat, 0, "**/", 3);

	if (pat->len && is_dir_sep(pat->buf[pat->len - 1]))
		strbuf_addstr(pat, "**");

	strbuf_release(&path);
	return prefix;
}