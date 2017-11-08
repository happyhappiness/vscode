void write_batch_csum_info(int *flist_entry, struct sum_struct *s)
{
	size_t i;
	int int_count;
	char filename[MAXPATHLEN];

	if (f_csums < 0) {
		stringjoin(filename, sizeof filename,
		    batch_prefix, rsync_csums_file, NULL);

		f_csums = do_open(filename, O_WRONLY | O_CREAT | O_TRUNC,
		    S_IRUSR | S_IWUSR);
		if (f_csums < 0) {
			rprintf(FERROR, "Batch file %s open error: %s\n",
			    filename, strerror(errno));
			close(f_csums);
			exit_cleanup(1);
		}
	}

	write_batch_csums_file(flist_entry, sizeof (int));
	int_count = s ? (int) s->count : 0;
	write_batch_csums_file(&int_count, sizeof int_count);

	if (s) {
		for (i = 0; i < s->count; i++) {
			write_batch_csums_file(&s->sums[i].sum1,
			    sizeof (uint32));
			write_batch_csums_file(s->sums[i].sum2, csum_length);
		}
	}
}