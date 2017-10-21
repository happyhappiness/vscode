		rprintf(FINFO,"count=%ld n=%ld rem=%ld\n",
			(long) s->count, (long) s->n, (long) s->remainder);

	if (s->count == 0) 
		return(s);

	s->sums = new_array(struct sum_buf, s->count);
	if (!s->sums) out_of_memory("receive_sums");

	for (i=0; i < (int) s->count;i++) {
		s->sums[i].sum1 = read_int(f);
		read_buf(f,s->sums[i].sum2,csum_length);

