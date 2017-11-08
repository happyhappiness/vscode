static void finish_filelist_progress(const struct file_list *flist)
{
	if (do_progress) {
		/* This overwrites the progress line */
		rprintf(FINFO, "%d file%sto consider\n",
			flist->used, flist->used == 1 ? " " : "s ");
	} else
		rprintf(FINFO, "done\n");
}