 static struct sum_struct *receive_sums(int f)
 {
 	struct sum_struct *s;
 	int i;
 	OFF_T offset = 0;
 
-	s = new(struct sum_struct);
-	if (!s) out_of_memory("receive_sums");
+	if (!(s = new(struct sum_struct)))
+		out_of_memory("receive_sums");
 
 	read_sum_head(f, s);
 
 	s->sums = NULL;
 
 	if (verbose > 3) {
