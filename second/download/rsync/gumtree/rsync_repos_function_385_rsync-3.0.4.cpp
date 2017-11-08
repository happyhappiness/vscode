int open_tmpfile(char *fnametmp, const char *fname, struct file_struct *file)
{
	int fd;

	if (!get_tmpname(fnametmp, fname))
		return -1;

	/* We initially set the perms without the setuid/setgid bits or group
	 * access to ensure that there is no race condition.  They will be
	 * correctly updated after the right owner and group info is set.
	 * (Thanks to snabb@epipe.fi for pointing this out.) */
	fd = do_mkstemp(fnametmp, file->mode & INITACCESSPERMS);

#if 0
	/* In most cases parent directories will already exist because their
	 * information should have been previously transferred, but that may
	 * not be the case with -R */
	if (fd == -1 && relative_paths && errno == ENOENT
	    && create_directory_path(fnametmp) == 0) {
		/* Get back to name with XXXXXX in it. */
		get_tmpname(fnametmp, fname);
		fd = do_mkstemp(fnametmp, file->mode & INITACCESSPERMS);
	}
#endif

	if (fd == -1) {
		rsyserr(FERROR_XFER, errno, "mkstemp %s failed",
			full_fname(fnametmp));
		return -1;
	}

	return fd;
}