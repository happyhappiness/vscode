int read_batch_csums_file(char *buff, int len)
{
	static int fdb_open = 1;
	int bytes_read;
	char filename[MAXPATHLEN];

	if (fdb_open) {
		/* Set up file extension */
		strlcpy(filename, batch_prefix, sizeof(filename));
		strlcat(filename, rsync_csums_file, sizeof(filename));

		/* Open batch flist file for reading */
		fdb = do_open(filename, O_RDONLY, 0);
		if (fdb == -1) {
			rprintf(FERROR, "Batch file %s open error: %s\n",
				filename, strerror(errno));
			close(fdb);
			exit_cleanup(1);
		}
		fdb_open = 0;
	}

	/* Read csums batch file */

	bytes_read = read(fdb, buff, len);

	if (bytes_read == -1) {
		rprintf(FERROR, "Batch file %s read error: %s\n",
			filename, strerror(errno));
		close(fdb);
		exit_cleanup(1);
	}

	return bytes_read;
}