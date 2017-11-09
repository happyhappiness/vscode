static int copy_altdest_file(const char *src, const char *dest, struct file_struct *file)
{
	char buf[MAXPATHLEN];
	const char *copy_to, *partialptr;
	int save_preserve_xattrs = preserve_xattrs;
	int ok, fd_w;

	if (inplace) {
		/* Let copy_file open the destination in place. */
		fd_w = -1;
		copy_to = dest;
	} else {
		fd_w = open_tmpfile(buf, dest, file);
		if (fd_w < 0)
			return -1;
		copy_to = buf;
	}
	cleanup_set(copy_to, NULL, NULL, -1, -1);
	if (copy_file(src, copy_to, fd_w, file->mode) < 0) {
		if (INFO_GTE(COPY, 1)) {
			rsyserr(FINFO, errno, "copy_file %s => %s",
				full_fname(src), copy_to);
		}
		/* Try to clean up. */
		unlink(copy_to);
		cleanup_disable();
		return -1;
	}
	partialptr = partial_dir ? partial_dir_fname(dest) : NULL;
	preserve_xattrs = 0; /* xattrs were copied with file */
	ok = finish_transfer(dest, copy_to, src, partialptr, file, 1, 0);
	preserve_xattrs = save_preserve_xattrs;
	cleanup_disable();
	return ok ? 0 : -1;
}