void write_batch_csum_info(int *flist_entry, int flist_count,
			   struct sum_struct *s)
{
	size_t i;
	int int_count;
	extern int csum_length;

	fdb_open = 1;

	write_batch_csums_file(flist_entry, sizeof(int));
	int_count = s ? (int) s->count : 0;
	write_batch_csums_file(&int_count, sizeof int_count);
	
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