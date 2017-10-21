		for (; j<s->count && targets[j].t == t; j++) {
			int i = targets[j].i;
			
			if (sum != s->sums[i].sum1) continue;
			
			if (verbose > 3)
				fprintf(FINFO,"potential match at %d target=%d %d sum=%08x\n",
					(int)offset,j,i,sum);
			
			if (!done_csum2) {
				int l = MIN(s->n,len-offset);
				map = (signed char *)map_ptr(buf,offset,l);
				get_checksum2((char *)map,l,sum2);
				done_csum2 = 1;
			}
			
			if (memcmp(sum2,s->sums[i].sum2,csum_length) != 0) {
				false_alarms++;
				continue;
			}
			
			matched(f,s,buf,offset,i);
			offset += s->sums[i].len - 1;
			k = MIN((len-offset), s->n);
			map = (signed char *)map_ptr(buf,offset,k);
			sum = get_checksum1((char *)map, k);
			s1 = sum & 0xFFFF;
			s2 = sum >> 16;
			matches++;
			break;
		}
		
	null_tag:
		/* Trim off the first byte from the checksum */
		map = (signed char *)map_ptr(buf,offset,k+1);
		s1 -= map[0] + CHAR_OFFSET;
		s2 -= k * (map[0]+CHAR_OFFSET);
		
		/* Add on the next byte (if there is one) to the checksum */
		if (k < (len-offset)) {
			s1 += (map[k]+CHAR_OFFSET);
