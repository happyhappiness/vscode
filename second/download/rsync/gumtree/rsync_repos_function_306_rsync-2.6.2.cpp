void flist_expand(struct file_list *flist)
{
	void *new_ptr;

	if (flist->count < flist->malloced)
		return;

	if (flist->malloced < FLIST_START)
		flist->malloced = FLIST_START;
	else if (flist->malloced >= FLIST_LINEAR)
		flist->malloced += FLIST_LINEAR;
	else
		flist->malloced *= 2;

	/*
	 * In case count jumped or we are starting the list
	 * with a known size just set it.
	 */
	if (flist->malloced < flist->count)
		flist->malloced = flist->count;

	if (flist->files) {
		new_ptr = realloc_array(flist->files,
		    struct file_struct *, flist->malloced);
	} else {
		new_ptr = new_array(struct file_struct *, flist->malloced);
	}

	if (verbose >= 2) {
		rprintf(FINFO, "[%s] expand file_list to %.0f bytes, did%s move\n",
		    who_am_i(),
		    (double) sizeof flist->files[0] * flist->malloced,
		    (new_ptr == flist->files) ? " not" : "");
	}

	flist->files = (struct file_struct **) new_ptr;

	if (!flist->files)
		out_of_memory("flist_expand");
}