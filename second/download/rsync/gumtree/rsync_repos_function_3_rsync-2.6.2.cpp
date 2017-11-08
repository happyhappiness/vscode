static void hash_search(int f,struct sum_struct *s,
			struct map_struct *buf, OFF_T len)
{
	OFF_T offset, end;
	unsigned int k;
	size_t last_i;
	char sum2[SUM_LENGTH];
	uint32 s1, s2, sum;
	schar *map;

	/* last_i is used to encourage adjacent matches, allowing the RLL coding of the
	   output to work more efficiently */
	last_i = (size_t)-1;

	if (verbose > 2) {
		rprintf(FINFO,"hash search b=%u len=%.0f\n",
			s->blength, (double)len);
	}

	k = MIN(len, s->blength);

	map = (schar *)map_ptr(buf, 0, k);

	sum = get_checksum1((char *)map, k);
	s1 = sum & 0xFFFF;
	s2 = sum >> 16;
	if (verbose > 3)
		rprintf(FINFO, "sum=%.8x k=%u\n", sum, k);

	offset = 0;

	end = len + 1 - s->sums[s->count-1].len;

	if (verbose > 3) {
		rprintf(FINFO, "hash search s->blength=%u len=%.0f count=%.0f\n",
			s->blength, (double)len, (double)s->count);
	}

	do {
		tag t = gettag2(s1,s2);
		int done_csum2 = 0;
		size_t j = tag_table[t];

		if (verbose > 4)
			rprintf(FINFO,"offset=%.0f sum=%08x\n",(double)offset,sum);

		if (j == NULL_TAG)
			goto null_tag;

		sum = (s1 & 0xffff) | (s2 << 16);
		tag_hits++;
		for (; j < s->count && targets[j].t == t; j++) {
			unsigned int l;
			size_t i = targets[j].i;

			if (sum != s->sums[i].sum1)
				continue;

			/* also make sure the two blocks are the same length */
			l = MIN((OFF_T)s->blength, len-offset);
			if (l != s->sums[i].len)
				continue;

			if (verbose > 3)
				rprintf(FINFO,"potential match at %.0f target=%.0f %.0f sum=%08x\n",
					(double)offset,(double)j,(double)i,sum);

			if (!done_csum2) {
				map = (schar *)map_ptr(buf,offset,l);
				get_checksum2((char *)map,l,sum2);
				done_csum2 = 1;
			}

			if (memcmp(sum2,s->sums[i].sum2,s->s2length) != 0) {
				false_alarms++;
				continue;
			}

			/* we've found a match, but now check to see
			 * if last_i can hint at a better match */
			for (j++; j < s->count && targets[j].t == t; j++) {
				size_t i2 = targets[j].i;
				if (i2 == last_i + 1) {
					if (sum != s->sums[i2].sum1)
						break;
					if (memcmp(sum2,s->sums[i2].sum2,s->s2length) != 0)
						break;
					/* we've found an adjacent match - the RLL coder
					 * will be happy */
					i = i2;
					break;
				}
			}

			last_i = i;

			matched(f,s,buf,offset,i);
			offset += s->sums[i].len - 1;
			k = MIN(s->blength, len-offset);
			map = (schar *)map_ptr(buf, offset, k);
			sum = get_checksum1((char *)map, k);
			s1 = sum & 0xFFFF;
			s2 = sum >> 16;
			matches++;
			break;
		}

	null_tag:
		/* Trim off the first byte from the checksum */
		map = (schar *)map_ptr(buf, offset, k+1);
		s1 -= map[0] + CHAR_OFFSET;
		s2 -= k * (map[0]+CHAR_OFFSET);

		/* Add on the next byte (if there is one) to the checksum */
		if (k < (len-offset)) {
			s1 += (map[k]+CHAR_OFFSET);
			s2 += s1;
		} else
			--k;

		/* By matching early we avoid re-reading the
		   data 3 times in the case where a token
		   match comes a long way after last
		   match. The 3 reads are caused by the
		   running match, the checksum update and the
		   literal send. */
		if (offset > last_match
		 && offset-last_match >= CHUNK_SIZE+s->blength
		 && end-offset > CHUNK_SIZE) {
			matched(f,s,buf,offset - s->blength, -2);
		}
	} while (++offset < end);

	matched(f,s,buf,len,-1);
	map_ptr(buf,len-1,1);
}