 
 static void dump_tags(void)
 {
 	static const char *msg = "fast-import";
 	struct tag *t;
 	struct ref_lock *lock;
-	char ref_name[PATH_MAX];
+	struct strbuf ref_name = STRBUF_INIT;
 
 	for (t = first_tag; t; t = t->next_tag) {
-		sprintf(ref_name, "tags/%s", t->name);
-		lock = lock_ref_sha1(ref_name, NULL);
+		strbuf_reset(&ref_name);
+		strbuf_addf(&ref_name, "tags/%s", t->name);
+		lock = lock_ref_sha1(ref_name.buf, NULL);
 		if (!lock || write_ref_sha1(lock, t->sha1, msg) < 0)
-			failure |= error("Unable to update %s", ref_name);
+			failure |= error("Unable to update %s", ref_name.buf);
 	}
+	strbuf_release(&ref_name);
 }
 
 static void dump_marks_helper(FILE *f,
 	uintmax_t base,
 	struct mark_set *m)
 {
