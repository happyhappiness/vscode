int is_hfs_dotgit(const char *path)
{
	ucs_char_t c;

	if (next_hfs_char(&path) != '.' ||
	    next_hfs_char(&path) != 'g' ||
	    next_hfs_char(&path) != 'i' ||
	    next_hfs_char(&path) != 't')
		return 0;
	c = next_hfs_char(&path);
	if (c && !is_dir_sep(c))
		return 0;

	return 1;
}