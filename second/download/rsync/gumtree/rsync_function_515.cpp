static void matched(int f,struct sum_struct *s,struct map_struct *buf,
		    off_t offset,int i)
{
	off_t n = offset - last_match;
	int j;

	if (verbose > 2 && i >= 0)
		fprintf(FINFO,"match at %d last_match=%d j=%d len=%d n=%d\n",
			(int)offset,(int)last_match,i,(int)s->sums[i].len,(int)n);

	send_token(f,i,buf,last_match,n,i==-1?0:s->sums[i].len);
	data_transfer += n;

	if (n > 0)
		write_flush(f);

	if (i >= 0)
		n += s->sums[i].len;
  
	for (j=0;j<n;j+=CHUNK_SIZE) {
		int n1 = MIN(CHUNK_SIZE,n-j);
		sum_update(map_ptr(buf,last_match+j,n1),n1);
	}


	if (i >= 0)
		last_match = offset + s->sums[i].len;
	else
		last_match = offset;
}