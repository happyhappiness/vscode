void write_batch_delta_file(char *buff, int bytes_to_write)
{
	char filename[MAXPATHLEN];

	if (f_delta < 0) {
		stringjoin(filename, sizeof filename,
		    batch_prefix, rsync_delta_file, NULL);

		f_delta = do_open(filename, O_WRONLY | O_CREAT | O_TRUNC,
				  S_IRUSR | S_IWUSR);
		if (f_delta < 0) {
			rprintf(FERROR, "Batch file %s open error: %s\n",
				filename, strerror(errno));
			exit_cleanup(1);
		}
	}

	if (write(f_delta, buff, bytes_to_write) < 0) {
		rprintf(FERROR, "Batch file %s write error: %s\n",
		    filename, strerror(errno));
		close(f_delta);
		exit_cleanup(1);
	}
}