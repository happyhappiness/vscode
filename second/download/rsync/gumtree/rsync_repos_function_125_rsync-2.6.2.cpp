void write_batch_csums_file(void *buff, int bytes_to_write)
{
	if (write(f_csums, buff, bytes_to_write) < 0) {
		rprintf(FERROR, "Batch file write error: %s\n",
		    strerror(errno));
		close(f_csums);
		exit_cleanup(1);
	}
}