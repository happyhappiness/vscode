 
 
 static off_t last_match;
 
 
 static void matched(int f,struct sum_struct *s,struct map_struct *buf,
-		    int offset,int i)
+		    off_t offset,int i)
 {
-  int n = offset - last_match;
-  int j;
+	off_t n = offset - last_match;
+	int j;
 
-  if (verbose > 2)
-    if (i != -1)
-      fprintf(FERROR,"match at %d last_match=%d j=%d len=%d n=%d\n",
-	      (int)offset,(int)last_match,i,(int)s->sums[i].len,n);
+	if (verbose > 2 && i >= 0)
+		fprintf(FINFO,"match at %d last_match=%d j=%d len=%d n=%d\n",
+			(int)offset,(int)last_match,i,(int)s->sums[i].len,(int)n);
 
-  send_token(f,i,buf,last_match,n,i==-1?0:s->sums[i].len);
-  data_transfer += n;
+	send_token(f,i,buf,last_match,n,i==-1?0:s->sums[i].len);
+	data_transfer += n;
 
-  if (n > 0)
-    write_flush(f);
+	if (n > 0)
+		write_flush(f);
 
-  if (i != -1)
-    n += s->sums[i].len;
+	if (i >= 0)
+		n += s->sums[i].len;
   
-  for (j=0;j<n;j+=CHUNK_SIZE) {
-    int n1 = MIN(CHUNK_SIZE,n-j);
-    sum_update(map_ptr(buf,last_match+j,n1),n1);
-  }
-
+	for (j=0;j<n;j+=CHUNK_SIZE) {
+		int n1 = MIN(CHUNK_SIZE,n-j);
+		sum_update(map_ptr(buf,last_match+j,n1),n1);
+	}
 
-  if (i != -1)
-    last_match = offset + s->sums[i].len;
 
+	if (i >= 0)
+		last_match = offset + s->sums[i].len;
+	else
+		last_match = offset;
 }
 
 
 static void hash_search(int f,struct sum_struct *s,
 			struct map_struct *buf,off_t len)
 {
-  int offset,j,k;
-  int end;
-  char sum2[SUM_LENGTH];
-  uint32 s1, s2, sum; 
-  signed char *map;
-
-  if (verbose > 2)
-    fprintf(FERROR,"hash search b=%d len=%d\n",s->n,(int)len);
-
-  k = MIN(len, s->n);
-
-  map = (signed char *)map_ptr(buf,0,k);
-
-  sum = get_checksum1((char *)map, k);
-  s1 = sum & 0xFFFF;
-  s2 = sum >> 16;
-  if (verbose > 3)
-    fprintf(FERROR, "sum=%.8x k=%d\n", sum, k);
-
-  offset = 0;
-
-  end = len + 1 - s->sums[s->count-1].len;
-
-  if (verbose > 3)
-    fprintf(FERROR,"hash search s->n=%d len=%d count=%d\n",
-	    s->n,(int)len,s->count);
-
-  do {
-    tag t = gettag2(s1,s2);
-    j = tag_table[t];
-    if (verbose > 4)
-      fprintf(FERROR,"offset=%d sum=%08x\n",
-	      offset,sum);
-
-    if (j != NULL_TAG) {
-      int done_csum2 = 0;
-
-      sum = (s1 & 0xffff) | (s2 << 16);
-      tag_hits++;
-      do {
-	int i = targets[j].i;
-
-	if (sum == s->sums[i].sum1) {
-	  if (verbose > 3)
-	    fprintf(FERROR,"potential match at %d target=%d %d sum=%08x\n",
-		    offset,j,i,sum);
-
-	  if (!done_csum2) {
-	    int l = MIN(s->n,len-offset);
-	    map = (signed char *)map_ptr(buf,offset,l);
-	    get_checksum2((char *)map,l,sum2);
-	    done_csum2 = 1;
-	  }
-	  if (memcmp(sum2,s->sums[i].sum2,csum_length) == 0) {
-	    matched(f,s,buf,offset,i);
-	    offset += s->sums[i].len - 1;
-	    k = MIN((len-offset), s->n);
-	    map = (signed char *)map_ptr(buf,offset,k);
-	    sum = get_checksum1((char *)map, k);
-	    s1 = sum & 0xFFFF;
-	    s2 = sum >> 16;
-	    ++matches;
-	    break;
-	  } else {
-	    false_alarms++;
-	  }
-	}
-	j++;
-      } while (j<s->count && targets[j].t == t);
-    }
-
-    /* Trim off the first byte from the checksum */
-    map = (signed char *)map_ptr(buf,offset,k+1);
-    s1 -= map[0] + CHAR_OFFSET;
-    s2 -= k * (map[0]+CHAR_OFFSET);
-
-    /* Add on the next byte (if there is one) to the checksum */
-    if (k < (len-offset)) {
-      s1 += (map[k]+CHAR_OFFSET);
-      s2 += s1;
-    } else {
-      --k;
-    }
-
-  } while (++offset < end);
-
-  matched(f,s,buf,len,-1);
-  map_ptr(buf,len-1,1);
+	off_t offset;
+	int j,k;
+	int end;
+	char sum2[SUM_LENGTH];
+	uint32 s1, s2, sum; 
+	signed char *map;
+
+	if (verbose > 2)
+		fprintf(FINFO,"hash search b=%d len=%d\n",s->n,(int)len);
+
+	k = MIN(len, s->n);
+	
+	map = (signed char *)map_ptr(buf,0,k);
+	
+	sum = get_checksum1((char *)map, k);
+	s1 = sum & 0xFFFF;
+	s2 = sum >> 16;
+	if (verbose > 3)
+		fprintf(FINFO, "sum=%.8x k=%d\n", sum, k);
+	
+	offset = 0;
+	
+	end = len + 1 - s->sums[s->count-1].len;
+	
+	if (verbose > 3)
+		fprintf(FINFO,"hash search s->n=%d len=%d count=%d\n",
+			s->n,(int)len,s->count);
+	
+	do {
+		tag t = gettag2(s1,s2);
+		int done_csum2 = 0;
+			
+		j = tag_table[t];
+		if (verbose > 4)
+			fprintf(FINFO,"offset=%d sum=%08x\n",(int)offset,sum);
+		
+		if (j == NULL_TAG) {
+			goto null_tag;
+		}
+
+		sum = (s1 & 0xffff) | (s2 << 16);
+		tag_hits++;
+		for (; j<s->count && targets[j].t == t; j++) {
+			int i = targets[j].i;
+			
+			if (sum != s->sums[i].sum1) continue;
+			
+			if (verbose > 3)
+				fprintf(FINFO,"potential match at %d target=%d %d sum=%08x\n",
+					(int)offset,j,i,sum);
+			
+			if (!done_csum2) {
+				int l = MIN(s->n,len-offset);
+				map = (signed char *)map_ptr(buf,offset,l);
+				get_checksum2((char *)map,l,sum2);
+				done_csum2 = 1;
+			}
+			
+			if (memcmp(sum2,s->sums[i].sum2,csum_length) != 0) {
+				false_alarms++;
+				continue;
+			}
+			
+			matched(f,s,buf,offset,i);
+			offset += s->sums[i].len - 1;
+			k = MIN((len-offset), s->n);
+			map = (signed char *)map_ptr(buf,offset,k);
+			sum = get_checksum1((char *)map, k);
+			s1 = sum & 0xFFFF;
+			s2 = sum >> 16;
+			matches++;
+			break;
+		}
+		
+	null_tag:
+		/* Trim off the first byte from the checksum */
+		map = (signed char *)map_ptr(buf,offset,k+1);
+		s1 -= map[0] + CHAR_OFFSET;
+		s2 -= k * (map[0]+CHAR_OFFSET);
+		
+		/* Add on the next byte (if there is one) to the checksum */
+		if (k < (len-offset)) {
+			s1 += (map[k]+CHAR_OFFSET);
+			s2 += s1;
+		} else {
+			--k;
+		}
+		
+	} while (++offset < end);
+	
+	matched(f,s,buf,len,-1);
+	map_ptr(buf,len-1,1);
 }
 
 
 void match_sums(int f,struct sum_struct *s,struct map_struct *buf,off_t len)
 {
-  char file_sum[MD4_SUM_LENGTH];
-
-  last_match = 0;
-  false_alarms = 0;
-  tag_hits = 0;
-  matches=0;
-  data_transfer=0;
-
-  sum_init();
-
-  if (len > 0 && s->count>0) {
-    build_hash_table(s);
+	char file_sum[MD4_SUM_LENGTH];
 
-    if (verbose > 2) 
-      fprintf(FERROR,"built hash table\n");
-
-    hash_search(f,s,buf,len);
-
-    if (verbose > 2) 
-      fprintf(FERROR,"done hash search\n");
-  } else {
-    matched(f,s,buf,len,-1);
-  }
+	last_match = 0;
+	false_alarms = 0;
+	tag_hits = 0;
+	matches=0;
+	data_transfer=0;
+
+	sum_init();
+
+	if (len > 0 && s->count>0) {
+		build_hash_table(s);
+		
+		if (verbose > 2) 
+			fprintf(FINFO,"built hash table\n");
+		
+		hash_search(f,s,buf,len);
+		
+		if (verbose > 2) 
+			fprintf(FINFO,"done hash search\n");
+	} else {
+		matched(f,s,buf,len,-1);
+	}
 
-  sum_end(file_sum);
+	sum_end(file_sum);
 
-  if (remote_version >= 14) {
-    if (verbose > 2)
-      fprintf(FERROR,"sending file_sum\n");
-    write_buf(f,file_sum,MD4_SUM_LENGTH);
-  }
-
-  if (targets) {
-    free(targets);
-    targets=NULL;
-  }
+	if (remote_version >= 14) {
+		if (verbose > 2)
+			fprintf(FINFO,"sending file_sum\n");
+		write_buf(f,file_sum,MD4_SUM_LENGTH);
+	}
 
-  if (verbose > 2)
-    fprintf(FERROR, "false_alarms=%d tag_hits=%d matches=%d\n",
-	    false_alarms, tag_hits, matches);
-
-  total_tag_hits += tag_hits;
-  total_false_alarms += false_alarms;
-  total_matches += matches;
-  total_data_transfer += data_transfer;
+	if (targets) {
+		free(targets);
+		targets=NULL;
+	}
+	
+	if (verbose > 2)
+		fprintf(FINFO, "false_alarms=%d tag_hits=%d matches=%d\n",
+			false_alarms, tag_hits, matches);
+	
+	total_tag_hits += tag_hits;
+	total_false_alarms += false_alarms;
+	total_matches += matches;
+	total_data_transfer += data_transfer;
 }
 
 void match_report(void)
 {
-  if (verbose <= 1)
-    return;
+	if (verbose <= 1)
+		return;
 
-  fprintf(FINFO,
-	  "total: matches=%d  tag_hits=%d  false_alarms=%d  data=%d\n",
-	  total_matches,total_tag_hits,
-	  total_false_alarms,total_data_transfer);
+	fprintf(FINFO,
+		"total: matches=%d  tag_hits=%d  false_alarms=%d  data=%ld\n",
+		total_matches,total_tag_hits,
+		total_false_alarms,(long)total_data_transfer);
 }
