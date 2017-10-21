  * Receive the checksums for a buffer
  **/
 static struct sum_struct *receive_sums(int f)
 {
 	struct sum_struct *s;
 	int32 i;
+	int lull_mod = allowed_lull * 5;
 	OFF_T offset = 0;
 
 	if (!(s = new(struct sum_struct)))
 		out_of_memory("receive_sums");
 
 	read_sum_head(f, s);
