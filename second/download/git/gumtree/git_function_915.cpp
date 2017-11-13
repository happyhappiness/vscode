static void process_log_file(void)
{
	struct stat st;
	if (fstat(get_lock_file_fd(&log_lock), &st)) {
		/*
		 * Perhaps there was an i/o error or another
		 * unlikely situation.  Try to make a note of
		 * this in gc.log along with any existing
		 * messages.
		 */
		int saved_errno = errno;
		fprintf(stderr, _("Failed to fstat %s: %s"),
			get_tempfile_path(&log_lock.tempfile),
			strerror(saved_errno));
		fflush(stderr);
		commit_lock_file(&log_lock);
		errno = saved_errno;
	} else if (st.st_size) {
		/* There was some error recorded in the lock file */
		commit_lock_file(&log_lock);
	} else {
		/* No error, clean up any old gc.log */
		unlink(git_path("gc.log"));
		rollback_lock_file(&log_lock);
	}
}