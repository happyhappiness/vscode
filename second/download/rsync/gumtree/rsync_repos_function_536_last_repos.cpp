static void interpret_stat_error(const char *fname, int is_dir)
{
	if (errno == ENOENT) {
		io_error |= IOERR_VANISHED;
		rprintf(FWARNING, "%s has vanished: %s\n",
			is_dir ? "directory" : "file", full_fname(fname));
	} else {
		io_error |= IOERR_GENERAL;
		rsyserr(FERROR_XFER, errno, "link_stat %s failed",
			full_fname(fname));
	}
}