static void handle_skipped_hlink(struct file_struct *file, int itemizing,
				 enum logcode code, int f_out)
{
	char fbuf[MAXPATHLEN];
	int new_last_ndx;
	struct file_list *save_flist = cur_flist;

	/* If we skip the last item in a chain of links and there was a
	 * prior non-skipped hard-link waiting to finish, finish it now. */
	if ((new_last_ndx = skip_hard_link(file, &cur_flist)) < 0)
		return;

	file = cur_flist->files[new_last_ndx - cur_flist->ndx_start];
	cur_flist->in_progress--; /* undo prior increment */
	f_name(file, fbuf);
	recv_generator(fbuf, file, new_last_ndx, itemizing, code, f_out);

	cur_flist = save_flist;
}