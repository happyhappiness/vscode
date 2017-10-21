 * entries.
 **/
static void flist_expand(struct file_list *flist)
{
	if (flist->count >= flist->malloced) {
		void *new_ptr;
		
		if (flist->malloced < 1000)
			flist->malloced += 1000;
		else
			flist->malloced *= 2;

		if (flist->files)
			new_ptr = realloc_array(flist->files,
						struct file_struct *,
						flist->malloced);
		else
			new_ptr = new_array(struct file_struct *,
					    flist->malloced);

		if (verbose >= 2) {
			rprintf(FINFO, "expand file_list to %.0f bytes, did%s move\n",
				(double)sizeof(flist->files[0])
				* flist->malloced,
				(new_ptr == flist->files) ? " not" : "");
		}
		
		flist->files = (struct file_struct **) new_ptr;

		if (!flist->files)
			out_of_memory("flist_expand");
	}
}
