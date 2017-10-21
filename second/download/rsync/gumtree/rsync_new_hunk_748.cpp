	 * In case count jumped or we are starting the list
	 * with a known size just set it.
	 */
	if (flist->malloced < flist->count)
		flist->malloced = flist->count;

	new_ptr = realloc_array(flist->files, struct file_struct *,
				flist->malloced);

	if (verbose >= 2) {
		rprintf(FINFO, "[%s] expand file_list to %.0f bytes, did%s move\n",
		    who_am_i(),
		    (double)sizeof flist->files[0] * flist->malloced,
		    (new_ptr == flist->files) ? " not" : "");
	}

	flist->files = new_ptr;

	if (!flist->files)
		out_of_memory("flist_expand");
}

void send_file_entry(struct file_struct *file, int f, unsigned short base_flags)
