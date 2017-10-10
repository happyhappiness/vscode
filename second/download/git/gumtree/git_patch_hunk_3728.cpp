 {
 	fprintf(stderr, "queue[%d] %s (%s) %s %06o %s\n",
 		x, one ? one : "",
 		s->path,
 		DIFF_FILE_VALID(s) ? "valid" : "invalid",
 		s->mode,
-		s->sha1_valid ? sha1_to_hex(s->sha1) : "");
+		s->oid_valid ? oid_to_hex(&s->oid) : "");
 	fprintf(stderr, "queue[%d] %s size %lu\n",
 		x, one ? one : "",
 		s->size);
 }
 
 void diff_debug_filepair(const struct diff_filepair *p, int i)
