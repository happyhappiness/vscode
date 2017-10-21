 			(long)s->count, s->blength, s->remainder);
 	}
 
 	if (s->count == 0)
 		return(s);
 
-	s->sums = new_array(struct sum_buf, s->count);
-	if (!s->sums) out_of_memory("receive_sums");
+	if (!(s->sums = new_array(struct sum_buf, s->count)))
+		out_of_memory("receive_sums");
 
-	for (i = 0; i < (int) s->count; i++) {
+	for (i = 0; i < (int)s->count; i++) {
 		s->sums[i].sum1 = read_int(f);
 		read_buf(f, s->sums[i].sum2, s->s2length);
 
 		s->sums[i].offset = offset;
-		s->sums[i].i = i;
+		s->sums[i].flags = 0;
 
-		if (i == (int) s->count-1 && s->remainder != 0) {
+		if (i == (int)s->count-1 && s->remainder != 0)
 			s->sums[i].len = s->remainder;
-		} else {
+		else
 			s->sums[i].len = s->blength;
-		}
 		offset += s->sums[i].len;
 
-		if (verbose > 3)
-			rprintf(FINFO, "chunk[%d] len=%d offset=%.0f sum1=%08x\n",
-				i, s->sums[i].len, (double)s->sums[i].offset, s->sums[i].sum1);
+		if (verbose > 3) {
+			rprintf(FINFO,
+				"chunk[%d] len=%d offset=%.0f sum1=%08x\n",
+				i, s->sums[i].len, (double)s->sums[i].offset,
+				s->sums[i].sum1);
+		}
 	}
 
 	s->flength = offset;
 
 	return s;
 }
