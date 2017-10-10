	 * dir->untracked is assigned. That function behaves
	 * differently when dir->untracked is non-NULL.
	 */
	if (!dir->untracked)
		dir->unmanaged_exclude_files++;
	el = add_exclude_list(dir, EXC_FILE, fname);
	if (add_excludes(fname, "", 0, el, NULL, sha1_stat) < 0)
		die("cannot use %s as an exclude file", fname);
}

void add_excludes_from_file(struct dir_struct *dir, const char *fname)
{
	dir->unmanaged_exclude_files++; /* see validate_untracked_cache() */
