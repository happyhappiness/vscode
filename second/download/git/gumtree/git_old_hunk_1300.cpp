static const char *tag_other = "";
static const char *tag_killed = "";
static const char *tag_modified = "";
static const char *tag_skip_worktree = "";
static const char *tag_resolve_undo = "";

static void write_eolinfo(const struct cache_entry *ce, const char *path)
{
	if (!show_eol)
		return;
	else {
		struct stat st;
		const char *i_txt = "";
		const char *w_txt = "";
		const char *a_txt = get_convert_attr_ascii(path);
		if (ce && S_ISREG(ce->ce_mode))
			i_txt = get_cached_convert_stats_ascii(ce->name);
		if (!lstat(path, &st) && S_ISREG(st.st_mode))
			w_txt = get_wt_convert_stats_ascii(path);
		printf("i/%-5s w/%-5s attr/%-17s\t", i_txt, w_txt, a_txt);
	}
}

static void write_name(const char *name)
{
	/*
	 * Prepend the super_prefix to name to construct the full_name to be
	 * written.
	 */
	struct strbuf full_name = STRBUF_INIT;
	if (super_prefix) {
		strbuf_addstr(&full_name, super_prefix);
		strbuf_addstr(&full_name, name);
		name = full_name.buf;
	}

	/*
	 * With "--full-name", prefix_len=0; this caller needs to pass
	 * an empty string in that case (a NULL is good for "").
	 */
	write_name_quoted_relative(name, prefix_len ? prefix : NULL,
				   stdout, line_terminator);

	strbuf_release(&full_name);
}

static void show_dir_entry(const char *tag, struct dir_entry *ent)
{
	int len = max_prefix_len;

	if (len >= ent->len)
		die("git ls-files: internal error - directory entry not superset of prefix");

	if (!dir_path_match(ent, &pathspec, len, ps_matched))
		return;

	fputs(tag, stdout);
	write_eolinfo(NULL, ent->name);
	write_name(ent->name);
}

static void show_other_files(struct dir_struct *dir)
{
	int i;

	for (i = 0; i < dir->nr; i++) {
		struct dir_entry *ent = dir->entries[i];
		if (!cache_name_is_other(ent->name, ent->len))
			continue;
		show_dir_entry(tag_other, ent);
	}
}

static void show_killed_files(struct dir_struct *dir)
{
	int i;
	for (i = 0; i < dir->nr; i++) {
		struct dir_entry *ent = dir->entries[i];
		char *cp, *sp;
		int pos, len, killed = 0;
