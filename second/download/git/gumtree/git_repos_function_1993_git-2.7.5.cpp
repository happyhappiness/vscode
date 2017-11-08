void add_excludes_from_file(struct dir_struct *dir, const char *fname)
{
	dir->unmanaged_exclude_files++; /* see validate_untracked_cache() */
	add_excludes_from_file_1(dir, fname, NULL);
}