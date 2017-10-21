
  if (verbose > 3)
    fprintf(stderr,"hash search s->n=%d len=%d count=%d\n",
	    s->n,(int)len,s->count);

  do {
    tag t = (s1 + s2) & 0xffff;		/* gettag(sum) */
    j = tag_table[t];
    if (verbose > 4)
      fprintf(stderr,"offset=%d sum=%08x\n",
	      offset,sum);

    if (j != NULL_TAG) {
      int done_csum2 = 0;

      sum = (s1 & 0xffff) + (s2 << 16);
      tag_hits++;
      do {
	int i = targets[j].i;

	if (sum == s->sums[i].sum1) {
	  if (verbose > 3)
