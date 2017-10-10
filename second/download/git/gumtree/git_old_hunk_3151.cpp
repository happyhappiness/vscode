		die("git ls-files: internal error - directory entry not superset of prefix");

	if (!dir_path_match(ent, &pathspec, len, ps_matched))
		return;

	fputs(tag, stdout);
	write_name(ent->name);
}

static void show_other_files(struct dir_struct *dir)
{
	int i;
