static void hash_search(int f,struct sum_struct *s,char *buf,off_t len)
{
  int offset,j,k;
  int end;
  char sum2[SUM_LENGTH];
  uint32 s1, s2, sum; 
  char *map;

  if (verbose > 2)
    fprintf(stderr,"hash search b=%d len=%d\n",s->n,(int)len);

  k = MIN(len, s->n);

  map = map_ptr(buf,0,k);

  sum = get_checksum1(map, k);
  s1 = sum & 0xFFFF;
  s2 = sum >> 16;
  if (verbose > 3)
    fprintf(stderr, "sum=%.8x k=%d\n", sum, k);

  offset = 0;

  end = len + 1 - s->sums[s->count-1].len;

  if (verbose > 3)
    fprintf(stderr,"hash search s->n=%d len=%d count=%d\n",
	    s->n,(int)len,s->count);

  do {
    tag t = gettag2(s1,s2);
    j = tag_table[t];
    if (verbose > 4)
      fprintf(stderr,"offset=%d sum=%08x\n",
	      offset,sum);

    if (j != NULL_TAG) {
      int done_csum2 = 0;

      sum = (s1 & 0xffff) | (s2 << 16);
      tag_hits++;
      do {
	int i = targets[j].i;

	if (sum == s->sums[i].sum1) {
	  if (verbose > 3)
	    fprintf(stderr,"potential match at %d target=%d %d sum=%08x\n",
		    offset,j,i,sum);

	  if (!done_csum2) {
	    int l = MIN(s->n,len-offset);
	    map = map_ptr(buf,offset,l);
	    get_checksum2(map,l,sum2);
	    done_csum2 = 1;
	  }
	  if (memcmp(sum2,s->sums[i].sum2,csum_length) == 0) {
	    matched(f,s,buf,len,offset,i);
	    offset += s->sums[i].len - 1;
	    k = MIN((len-offset), s->n);
	    map = map_ptr(buf,offset,k);
	    sum = get_checksum1(map, k);
	    s1 = sum & 0xFFFF;
	    s2 = sum >> 16;
	    ++matches;
	    break;
	  } else {
	    false_alarms++;
	  }
	}
	j++;
      } while (j<s->count && targets[j].t == t);
    }

    /* Trim off the first byte from the checksum */
    map = map_ptr(buf,offset,k+1);
    s1 -= map[0];
    s2 -= k * map[0];

    /* Add on the next byte (if there is one) to the checksum */
    if (k < (len-offset)) {
      s1 += map[k];
      s2 += s1;
    } else {
      --k;
    }

  } while (++offset < end);

  matched(f,s,buf,len,len,-1);
}