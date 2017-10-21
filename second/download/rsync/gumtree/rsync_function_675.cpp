static void flist_expand(struct file_list *flist)
{
	if (flist->count >= flist->malloced) {
		size_t new_bytes;
		void *new_ptr;
		
		if (flist->malloced < 1000)
			flist->malloced += 1000;
		else
			flist->malloced *= 2;

		new_bytes = sizeof(flist->files[0]) * flist->malloced;
		
		new_ptr = realloc(flist->files, new_bytes);

		if (verbose >= 2) {
			rprintf(FINFO, RSYNC_NAME ": expand file_list to %.0f bytes, did%s move\n",
				(double) new_bytes,
				(new_ptr == flist->files) ? " not" : "");
		}
		
		flist->files = (struct file_struct **) new_ptr;

		if (!flist->files)
			out_of_memory("flist_expand");
	}
}