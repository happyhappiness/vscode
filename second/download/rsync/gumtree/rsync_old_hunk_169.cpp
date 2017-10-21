  s->count = read_int(f);
  s->n = read_int(f);
  s->remainder = read_int(f);  
  s->sums = NULL;

  if (verbose > 3)
    fprintf(stderr,"count=%d n=%d rem=%d\n",
	    s->count,s->n,s->remainder);

  block_len = s->n;

  if (s->count == 0) 
    return(s);
