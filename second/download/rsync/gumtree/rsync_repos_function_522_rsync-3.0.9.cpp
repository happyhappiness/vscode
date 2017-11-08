void clear_file(struct file_struct *file)
{
	/* The +1 zeros out the first char of the basename. */
	memset(file, 0, FILE_STRUCT_LEN + 1);
	/* In an empty entry, F_DEPTH() is an offset to the next non-empty
	 * entry.  Likewise for len32 in the opposite direction.  We assume
	 * that we're alone for now since flist_find() will adjust the counts
	 * it runs into that aren't up-to-date. */
	file->len32 = F_DEPTH(file) = 1;
}