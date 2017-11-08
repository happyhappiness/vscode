void write_batch_delta_file(char *buff, int bytes_to_write)
{
	static int fdb_delta_open = 1;
	char filename[MAXPATHLEN];

	if (fdb_delta_open) {
		/* Set up file extension */
		strlcpy(filename, batch_prefix, sizeof(filename));
		strlcat(filename, rsync_delta_file, sizeof(filename));

		/*
		 * Open batch delta file for writing;
		 * create it if it doesn't exist
		 */
		fdb_delta = do_open(filename, O_WRONLY | O_CREAT | O_TRUNC,
			    S_IREAD | S_IWRITE);
		if (fdb_delta == -1) {
			rprintf(FERROR, "Batch file %s open error: %s\n",
				filename, strerror(errno));
			close(fdb_delta);
			exit_cleanup(1);
		}
		fdb_delta_open = 0;
	}

	/* Write buffer to batch delta file */

	if (write(fdb_delta, buff, bytes_to_write) == -1) {
		rprintf(FERROR, "Batch file %s write error: %s\n",
			filename, strerror(errno));
		close(fdb_delta);
		exit_cleanup(1);
	}
}