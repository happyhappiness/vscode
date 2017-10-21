	s->count = read_int(f);
	s->n = read_int(f);
	s->remainder = read_int(f);  
	s->sums = NULL;

	if (verbose > 3)
		rprintf(FINFO,"count=%d n=%d rem=%d\n",
			s->count,s->n,s->remainder);

	if (s->count == 0) 
		return(s);

	s->sums = (struct sum_buf *)malloc(sizeof(s->sums[0])*s->count);
	if (!s->sums) out_of_memory("receive_sums");
