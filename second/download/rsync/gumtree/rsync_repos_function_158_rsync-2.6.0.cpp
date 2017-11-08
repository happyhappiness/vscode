static struct sum_struct *receive_sums(int f)
{
	struct sum_struct *s;
	int i;
	OFF_T offset = 0;

	s = new(struct sum_struct);
	if (!s) out_of_memory("receive_sums");

	read_sum_head(f, s);

	s->sums = NULL;

	if (verbose > 3)
		rprintf(FINFO, "count=%ld n=%ld rem=%ld\n",
			(long) s->count, (long) s->blength,
			(long) s->remainder);

	if (s->count == 0)
		return(s);

	s->sums = new_array(struct sum_buf, s->count);
	if (!s->sums) out_of_memory("receive_sums");

	for (i = 0; i < (int) s->count; i++) {
		s->sums[i].sum1 = read_int(f);
		read_buf(f, s->sums[i].sum2, s->s2length);

		s->sums[i].offset = offset;
		s->sums[i].i = i;

		if (i == (int) s->count-1 && s->remainder != 0) {
			s->sums[i].len = s->remainder;
		} else {
			s->sums[i].len = s->blength;
		}
		offset += s->sums[i].len;

		if (verbose > 3)
			rprintf(FINFO, "chunk[%d] len=%d offset=%.0f sum1=%08x\n",
				i, s->sums[i].len, (double)s->sums[i].offset, s->sums[i].sum1);
	}

	s->flength = offset;

	return s;
}