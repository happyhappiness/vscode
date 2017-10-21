  * Receive the checksums for a buffer
  **/
 static struct sum_struct *receive_sums(int f)
 {
 	struct sum_struct *s;
 	int32 i;
-	int lull_mod = allowed_lull * 5;
+	int lull_mod = protocol_version >= 31 ? 0 : allowed_lull * 5;
 	OFF_T offset = 0;
 
 	if (!(s = new(struct sum_struct)))
 		out_of_memory("receive_sums");
 
 	read_sum_head(f, s);
 
 	s->sums = NULL;
 
-	if (verbose > 3) {
-		rprintf(FINFO, "count=%.0f n=%ld rem=%ld\n",
-			(double)s->count, (long)s->blength, (long)s->remainder);
+	if (DEBUG_GTE(DELTASUM, 3)) {
+		rprintf(FINFO, "count=%s n=%ld rem=%ld\n",
+			big_num(s->count), (long)s->blength, (long)s->remainder);
 	}
 
 	if (append_mode > 0) {
 		s->flength = (OFF_T)s->count * s->blength;
 		if (s->remainder)
 			s->flength -= s->blength - s->remainder;
