void write_batch_flist_file(char *buff, int bytes_to_write)
{
	char filename[MAXPATHLEN];

	if (fdb_open) {
		/* Set up file extension */
		strlcpy(filename, batch_prefix, sizeof(filename));
		strlcat(filename, rsync_flist_file, sizeof(filename));

		/*
		 * Open batch flist file for writing;
		 * create it if it doesn't exist
		 */
		fdb = do_open(filename, O_WRONLY | O_CREAT | O_TRUNC,
			    S_IREAD | S_IWRITE);
		if (fdb == -1) {
			rprintf(FERROR, "Batch file %s open error: %s\n",
				filename, strerror(errno));
			close(fdb);
			exit_cleanup(1);
		}
		fdb_open = 0;
	}

	/* Write buffer to batch flist file */

	if (write(fdb, buff, bytes_to_write) == -1) {
		rprintf(FERROR, "Batch file %s write error: %s\n",
			filename, strerror(errno));
		close(fdb);
		exit_cleanup(1);
	}

	if (fdb_close) {
		close(fdb);
	}
}