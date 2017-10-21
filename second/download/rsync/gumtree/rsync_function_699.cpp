static struct sum_struct *generate_sums(struct map_struct *buf,OFF_T len,int n)
{
	int i;
	struct sum_struct *s;
	int count;
	int block_len = n;
	int remainder = (len%block_len);
	OFF_T offset = 0;

	count = (len+(block_len-1))/block_len;

	s = (struct sum_struct *)malloc(sizeof(*s));
	if (!s) out_of_memory("generate_sums");

	s->count = count;
	s->remainder = remainder;
	s->n = n;
	s->flength = len;

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
		char *map = map_ptr(buf,offset,n1);

		s->sums[i].sum1 = get_checksum1(map,n1);
		get_checksum2(map,n1,s->sums[i].sum2);

		s->sums[i].offset = offset;
		s->sums[i].len = n1;
		s->sums[i].i = i;

		if (verbose > 3)
			rprintf(FINFO,"chunk[%d] offset=%.0f len=%d sum1=%08x\n",
				i,(double)s->sums[i].offset,s->sums[i].len,s->sums[i].sum1);

		len -= n1;
		offset += n1;
	}

	return s;
}