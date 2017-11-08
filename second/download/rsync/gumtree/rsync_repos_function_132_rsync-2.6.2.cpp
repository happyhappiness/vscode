int read_batch_delta_file(char *buff, int len)
{
	int bytes_read;
	char filename[MAXPATHLEN];

	if (f_delta < 0) {
		stringjoin(filename, sizeof filename,
		    batch_prefix, rsync_delta_file, NULL);

		f_delta = do_open(filename, O_RDONLY, 0);
		if (f_delta < 0) {
			rprintf(FERROR, "Batch file %s open error: %s\n",
			    filename, strerror(errno));
			close(f_delta);
			exit_cleanup(1);
		}
	}

	bytes_read = read(f_delta, buff, len);
	if (bytes_read < 0) {
		rprintf(FERROR, "Batch file %s read error: %s\n",
		    filename, strerror(errno));
		close(f_delta);
		exit_cleanup(1);
	}

	return bytes_read;
}