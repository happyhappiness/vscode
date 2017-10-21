	if (!s) out_of_memory("receive_sums");

	read_sum_head(f, s);

	s->sums = NULL;

	if (verbose > 3) {
		rprintf(FINFO, "count=%ld n=%u rem=%u\n",
			(long)s->count, s->blength, s->remainder);
	}

	if (s->count == 0)
		return(s);

	s->sums = new_array(struct sum_buf, s->count);
	if (!s->sums) out_of_memory("receive_sums");
