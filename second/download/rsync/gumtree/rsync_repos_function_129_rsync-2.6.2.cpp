void read_batch_csum_info(int flist_entry, struct sum_struct *s,
			  int *checksums_match)
{
	int i;
	int file_flist_entry;
	int file_chunk_ct;
	uint32 file_sum1;
	char file_sum2[SUM_LENGTH];
	char filename[MAXPATHLEN];

	if (f_csums < 0) {
		stringjoin(filename, sizeof filename,
		    batch_prefix, rsync_csums_file, NULL);

		f_csums = do_open(filename, O_RDONLY, 0);
		if (f_csums < 0) {
			rprintf(FERROR, "Batch file %s open error: %s\n",
			    filename, strerror(errno));
			close(f_csums);
			exit_cleanup(1);
		}
	}

	read_batch_csums_file((char *) &file_flist_entry, sizeof (int));
	if (file_flist_entry != flist_entry) {
		rprintf(FINFO, "file_flist_entry (%d) != flist_entry (%d)\n",
		    file_flist_entry, flist_entry);
		close(f_csums);
		exit_cleanup(1);

	} else {
		read_batch_csums_file((char *) &file_chunk_ct, sizeof (int));
		*checksums_match = 1;
		for (i = 0; i < file_chunk_ct; i++) {
			read_batch_csums_file((char *) &file_sum1,
			    sizeof (uint32));
			read_batch_csums_file(file_sum2, csum_length);

			if ((s->sums[i].sum1 != file_sum1)
			    || memcmp(s->sums[i].sum2, file_sum2, csum_length))
				*checksums_match = 0;
		}		/*  end for  */
	}
}