int read_batch_csums_file(char *buff, int len)
{
	int bytes_read;

	if ((bytes_read = read(f_csums, buff, len)) < 0) {
		rprintf(FERROR, "Batch file read error: %s\n", strerror(errno));
		close(f_csums);
		exit_cleanup(1);
	}
	return bytes_read;
}