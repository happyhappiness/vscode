		    int offset,int i)
{
  int n = offset - last_match;
  
  if (verbose > 2)
    if (i != -1)
      fprintf(stderr,"match at %d last_match=%d j=%d len=%d n=%d\n",
	      (int)offset,(int)last_match,i,(int)s->sums[i].len,n);

  if (n > 0) {
    int l = 0;
    write_int(f,n);
    while (l < n) {
