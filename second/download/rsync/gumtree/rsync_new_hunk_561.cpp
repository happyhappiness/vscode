	if (count==0) {
		s->sums = NULL;
		return s;
	}

	if (verbose > 3)
		rprintf(FINFO,"count=%d rem=%d n=%d flength=%.0f\n",
			s->count,s->remainder,s->n,(double)s->flength);

	s->sums = (struct sum_buf *)malloc(sizeof(s->sums[0])*s->count);
	if (!s->sums) out_of_memory("generate_sums");
  
	for (i=0;i<count;i++) {
		int n1 = MIN(len,n);
