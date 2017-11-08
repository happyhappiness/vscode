int read_batch_flist_file(char *buff, int len)
{
	int bytes_read;
	char filename[MAXPATHLEN];

	if (fdb_open) {
		/* Set up file extension */
		strlcpy(filename, batch_prefix, sizeof(filename));
		strlcat(filename, rsync_flist_file, sizeof(filename));

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

	/* Read flist batch file */

	switch (bytes_read = read(fdb, buff, len)) {
	    case -1:
		rprintf(FERROR, "Batch file %s read error: %s\n",
			filename, strerror(errno));
		close(fdb);
		exit_cleanup(1);
		break;
	    case 0:	/* EOF */
		close(fdb);
	}

	return bytes_read;
}