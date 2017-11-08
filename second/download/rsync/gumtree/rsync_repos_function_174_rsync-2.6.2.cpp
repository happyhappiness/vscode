static void generate_and_send_sums(struct map_struct *buf, size_t len, int f_out)
{
	size_t i;
	struct sum_struct sum;
	OFF_T offset = 0;

	sum_sizes_sqroot(&sum, len);

	write_sum_head(f_out, &sum);

	for (i = 0; i < sum.count; i++) {
		unsigned int n1 = MIN(len, sum.blength);
		char *map = map_ptr(buf, offset, n1);
		uint32 sum1 = get_checksum1(map, n1);
		char sum2[SUM_LENGTH];

		get_checksum2(map, n1, sum2);

		if (verbose > 3) {
			rprintf(FINFO,
				"chunk[%.0f] offset=%.0f len=%u sum1=%08lx\n",
				(double)i, (double)offset, n1,
				(unsigned long)sum1);
		}
		write_int(f_out, sum1);
		write_buf(f_out, sum2, sum.s2length);
		len -= n1;
		offset += n1;
	}
}