int flist_find_ignore_dirness(struct file_list *flist, struct file_struct *f)
{
	mode_t save_mode;
	int ndx;

	/* First look for an item that agrees in directory-ness. */
	ndx = flist_find(flist, f);
	if (ndx >= 0)
		return ndx;

	/* Temporarily flip f->mode to look for an item of opposite
	 * directory-ness. */
	save_mode = f->mode;
	f->mode = S_ISDIR(f->mode) ? S_IFREG : S_IFDIR;
	ndx = flist_find(flist, f);
	f->mode = save_mode;
	return ndx;
}