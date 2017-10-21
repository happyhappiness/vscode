 	else
 		return local_server;
 }
 
 
 /*
-  generate a stream of signatures/checksums that describe a buffer
-
-  generate approximately one checksum every n bytes
-  */
-static struct sum_struct *generate_sums(struct map_struct *buf,OFF_T len,int n)
+ * Generate and send a stream of signatures/checksums that describe a buffer
+ *
+ * Generate approximately one checksum every block_len bytes.
+ */
+static void generate_and_send_sums(struct map_struct *buf, OFF_T len,
+				   int block_len, int f_out)
 {
-	int i;
-	struct sum_struct *s;
-	int count;
-	int block_len = n;
-	int remainder = (len%block_len);
+	size_t i;
+	struct sum_struct sum;
 	OFF_T offset = 0;
 
-	count = (len+(block_len-1))/block_len;
-
-	s = (struct sum_struct *)malloc(sizeof(*s));
-	if (!s) out_of_memory("generate_sums");
-
-	s->count = count;
-	s->remainder = remainder;
-	s->n = n;
-	s->flength = len;
-
-	if (count==0) {
-		s->sums = NULL;
-		return s;
-	}
-
-	if (verbose > 3)
-		rprintf(FINFO,"count=%d rem=%d n=%d flength=%.0f\n",
-			s->count,s->remainder,s->n,(double)s->flength);
-
-	s->sums = (struct sum_buf *)malloc(sizeof(s->sums[0])*s->count);
-	if (!s->sums) out_of_memory("generate_sums");
-  
-	for (i=0;i<count;i++) {
-		int n1 = MIN(len,n);
-		char *map = map_ptr(buf,offset,n1);
-
-		s->sums[i].sum1 = get_checksum1(map,n1);
-		get_checksum2(map,n1,s->sums[i].sum2);
-
-		s->sums[i].offset = offset;
-		s->sums[i].len = n1;
-		s->sums[i].i = i;
-
-		if (verbose > 3)
-			rprintf(FINFO,"chunk[%d] offset=%.0f len=%d sum1=%08x\n",
-				i,(double)s->sums[i].offset,s->sums[i].len,s->sums[i].sum1);
-
+	sum.count = (len + (block_len - 1)) / block_len;
+	sum.remainder = (len % block_len);
+	sum.n = block_len;
+	sum.flength = len;
+	/* not needed here  sum.sums = NULL; */
+
+	if (sum.count && verbose > 3) {
+		rprintf(FINFO, "count=%ld rem=%ld n=%ld flength=%.0f\n",
+			(long) sum.count, (long) sum.remainder,
+			(long) sum.n, (double) sum.flength);
+	}
+
+	write_int(f_out, sum.count);
+	write_int(f_out, sum.n);
+	write_int(f_out, sum.remainder);
+
+	for (i = 0; i < sum.count; i++) {
+		int n1 = MIN(len, block_len);
+		char *map = map_ptr(buf, offset, n1);
+		uint32 sum1 = get_checksum1(map, n1);
+		char sum2[SUM_LENGTH];
+
+		get_checksum2(map, n1, sum2);
+
+		if (verbose > 3) {
+			rprintf(FINFO,
+				"chunk[%d] offset=%.0f len=%d sum1=%08lx\n",
+				i, (double) offset, n1, (unsigned long) sum1);
+		}
+		write_int(f_out, sum1);
+		write_buf(f_out, sum2, csum_length);
 		len -= n1;
 		offset += n1;
 	}
-
-	return s;
 }
 
 
 
-/*
- * Acts on file number I from FLIST, whose name is fname.
+/**
+ * Acts on file number @p i from @p flist, whose name is @p fname.
  *
  * First fixes up permissions, then generates checksums for the file.
  *
- * (This comment was added later by mbp who was trying to work it out;
- * it might be wrong.)
- */ 
-void recv_generator(char *fname,struct file_list *flist,int i,int f_out)
+ * @note This comment was added later by mbp who was trying to work it
+ * out.  It might be wrong.
+ **/ 
+void recv_generator(char *fname, struct file_list *flist, int i, int f_out)
 {  
 	int fd;
 	STRUCT_STAT st;
 	struct map_struct *buf;
-	struct sum_struct *s;
 	int statret;
 	struct file_struct *file = flist->files[i];
 	char *fnamecmp;
 	char fnamecmpbuf[MAXPATHLEN];
 	extern char *compare_dest;
 	extern int list_only;
 	extern int preserve_perms;
 	extern int only_existing;
+	extern int orig_umask;
 
 	if (list_only) return;
 
 	if (verbose > 2)
 		rprintf(FINFO,"recv_generator(%s,%d)\n",fname,i);
 
