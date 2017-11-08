void flist_free(struct file_list *flist)
{
	int i;
	for (i = 1; i < flist->count; i++) {
		if (!flist->string_area)
			free_file(flist->files[i]);
		free(flist->files[i]);
	}
	/* FIXME: I don't think we generally need to blank the flist
	 * since it's about to be freed.  This will just cause more
	 * memory traffic.  If you want a freed-memory debugger, you
	 * know where to get it. */
	memset((char *) flist->files, 0,
	       sizeof(flist->files[0]) * flist->count);
	free(flist->files);
	if (flist->string_area)
		string_area_free(flist->string_area);
	memset((char *) flist, 0, sizeof(*flist));
	free(flist);
}