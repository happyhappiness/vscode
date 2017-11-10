int is_hfs_dotgit(const char *path)
{
	ucs_char_t c;

	c = next_hfs_char(&path);
	if (c != '.')
		return 0;
	c = next_hfs_char(&path);

	/*
	 * there's a great deal of other case-folding that occurs
	 * in HFS+, but this is enough to catch anything that will
	 * convert to ".git"
	 */
	if (c != 'g' && c != 'G')
		return 0;
	c = next_hfs_char(&path);
	if (c != 'i' && c != 'I')
		return 0;
	c = next_hfs_char(&path);
	if (c != 't' && c != 'T')
		return 0;
	c = next_hfs_char(&path);
	if (c && !is_dir_sep(c))
		return 0;

	return 1;
}