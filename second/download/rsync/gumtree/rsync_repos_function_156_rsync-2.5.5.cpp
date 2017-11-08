static void send_sums(struct sum_struct *s, int f_out)
{
	if (s) {
		size_t i;

		/* tell the other guy how many we are going to be
		   doing and how many bytes there are in the last
		   chunk */
		write_int(f_out, s->count);
		write_int(f_out, s->n);
		write_int(f_out, s->remainder);

		for (i = 0; i < s->count; i++) {
			write_int(f_out, s->sums[i].sum1);
			write_buf(f_out, s->sums[i].sum2, csum_length);
		}
	} else {
		/* we don't have checksums */
		write_int(f_out, 0);
		write_int(f_out, block_size);
		write_int(f_out, 0);
	}
}