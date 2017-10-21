	else
		last_match = offset;
}


static void hash_search(int f,struct sum_struct *s,
			struct map_struct *buf,off_t len)
{
	off_t offset;
	int j,k;
	int end;
	char sum2[SUM_LENGTH];
	uint32 s1, s2, sum; 
	signed char *map;

	if (verbose > 2)
		fprintf(FINFO,"hash search b=%d len=%d\n",s->n,(int)len);

	k = MIN(len, s->n);
	
	map = (signed char *)map_ptr(buf,0,k);
	
	sum = get_checksum1((char *)map, k);
	s1 = sum & 0xFFFF;
	s2 = sum >> 16;
	if (verbose > 3)
		fprintf(FINFO, "sum=%.8x k=%d\n", sum, k);
	
	offset = 0;
	
	end = len + 1 - s->sums[s->count-1].len;
	
	if (verbose > 3)
		fprintf(FINFO,"hash search s->n=%d len=%d count=%d\n",
			s->n,(int)len,s->count);
	
	do {
		tag t = gettag2(s1,s2);
		int done_csum2 = 0;
			
		j = tag_table[t];
		if (verbose > 4)
			fprintf(FINFO,"offset=%d sum=%08x\n",(int)offset,sum);
		
		if (j == NULL_TAG) {
			goto null_tag;
		}

		sum = (s1 & 0xffff) | (s2 << 16);
