void write_batch_csum_info(int *flist_entry, int flist_count,
			   struct sum_struct *s)
{
	size_t i;
	size_t int_zero = 0;
	extern int csum_length;

	fdb_open = 1;

	/* Write csum info to batch file */

	/* FIXME: This will break if s->count is ever not exactly an int. */
	write_batch_csums_file(flist_entry, sizeof(int));
	write_batch_csums_file(s ? &s->count : &int_zero, sizeof(int));
	
	if (s) {
		for (i = 0; i < s->count; i++) {
			write_batch_csums_file(&s->sums[i].sum1, sizeof(uint32));
			if ((*flist_entry == flist_count - 1)
			    && (i == s->count - 1)) {
				fdb_close = 1;
			}
			write_batch_csums_file(s->sums[i].sum2, csum_length);
		}
	}
}