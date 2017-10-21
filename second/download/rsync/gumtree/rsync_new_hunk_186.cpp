	  if (verbose > 3)
	    fprintf(FERROR,"potential match at %d target=%d %d sum=%08x\n",
		    offset,j,i,sum);

	  if (!done_csum2) {
	    int l = MIN(s->n,len-offset);
	    map = window_ptr(buf,offset,l);
	    get_checksum2(map,l,sum2);
	    done_csum2 = 1;
	  }
	  if (memcmp(sum2,s->sums[i].sum2,csum_length) == 0) {
	    matched(f,s,buf,len,offset,i);
	    offset += s->sums[i].len - 1;
	    k = MIN((len-offset), s->n);
	    map = window_ptr(buf,offset,k);
	    sum = get_checksum1(map, k);
	    s1 = sum & 0xFFFF;
	    s2 = sum >> 16;
	    ++matches;
	    break;
	  } else {
