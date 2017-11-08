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