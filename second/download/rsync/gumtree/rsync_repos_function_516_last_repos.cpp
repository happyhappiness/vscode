static void finish_filelist_progress(const struct file_list *flist)
{
	if (INFO_GTE(FLIST, 2)) {
		/* This overwrites the progress line */
		rprintf(FINFO, "%d file%sto consider\n",
			flist->used, flist->used == 1 ? " " : "s ");
	} else {
		output_needs_newline = 0;
		rprintf(FINFO, "done\n");
	}
}