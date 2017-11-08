static int get_next_gen_ndx(int fd, int next_gen_ndx, int desired_ndx)
{
	while (next_gen_ndx < desired_ndx) {
		if (next_gen_ndx >= 0) {
			struct file_struct *file = cur_flist->files[next_gen_ndx];
			rprintf(FERROR_XFER,
				"(No batched update for%s \"%s\")\n",
				file->flags & FLAG_FILE_SENT ? " resend of" : "",
				f_name(file, NULL));
		}
		next_gen_ndx = read_int(fd);
		if (next_gen_ndx == -1) {
			if (inc_recurse)
				next_gen_ndx = first_flist->prev->used + first_flist->prev->ndx_start;
			else
				next_gen_ndx = cur_flist->used;
		}
	}
	return next_gen_ndx;
}