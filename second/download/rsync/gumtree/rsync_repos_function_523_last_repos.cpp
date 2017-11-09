static void flist_expand(struct file_list *flist, int extra)
{
	struct file_struct **new_ptr;

	if (flist->used + extra <= flist->malloced)
		return;

	if (flist->malloced < FLIST_START)
		flist->malloced = FLIST_START;
	else if (flist->malloced >= FLIST_LINEAR)
		flist->malloced += FLIST_LINEAR;
	else
		flist->malloced *= 2;

	/* In case count jumped or we are starting the list
	 * with a known size just set it. */
	if (flist->malloced < flist->used + extra)
		flist->malloced = flist->used + extra;

	new_ptr = realloc_array(flist->files, struct file_struct *,
				flist->malloced);

	if (DEBUG_GTE(FLIST, 1) && flist->malloced != FLIST_START) {
		rprintf(FCLIENT, "[%s] expand file_list pointer array to %s bytes, did%s move\n",
		    who_am_i(),
		    big_num(sizeof flist->files[0] * flist->malloced),
		    (new_ptr == flist->files) ? " not" : "");
	}

	flist->files = new_ptr;

	if (!flist->files)
		out_of_memory("flist_expand");
}