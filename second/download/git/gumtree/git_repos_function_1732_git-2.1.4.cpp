void add_excludes_from_file(struct dir_struct *dir, const char *fname)
{
	struct exclude_list *el;
	el = add_exclude_list(dir, EXC_FILE, fname);
	if (add_excludes_from_file_to_list(fname, "", 0, el, 0) < 0)
		die("cannot use %s as an exclude file", fname);
}