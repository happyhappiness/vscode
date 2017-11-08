int read_batch_delta_file(char *buff, int len)
{
	static int fdb_delta_open = 1;
	int bytes_read;
	char filename[MAXPATHLEN];

	if (fdb_delta_open) {
		/* Set up file extension */
		strlcpy(filename, batch_prefix, sizeof(filename));
		strlcat(filename, rsync_delta_file, sizeof(filename));

		/* Open batch flist file for reading */
		fdb_delta = do_open(filename, O_RDONLY, 0);
		if (fdb_delta == -1) {
			rprintf(FERROR, "Batch file %s open error: %s\n",
				filename, strerror(errno));
			close(fdb_delta);
			exit_cleanup(1);
		}
		fdb_delta_open = 0;
	}

	/* Read delta batch file */

	bytes_read = read(fdb_delta, buff, len);

	if (bytes_read == -1) {
		rprintf(FERROR, "Batch file %s read error: %s\n",
			filename, strerror(errno));
		close(fdb_delta);
		exit_cleanup(1);
	}

	return bytes_read;
}