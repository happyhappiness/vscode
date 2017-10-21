 static struct exclude_struct **local_exclude_list;
 
 static struct file_struct null_file;
 
 static void clean_flist(struct file_list *flist, int strip_root);
 
+
+static int show_build_progress_p(void)
+{
+	extern int do_progress;
+
+	return do_progress && verbose && recurse && !am_server;
+}
+
+/**
+ * True if we're local, etc, and should emit progress emssages.
+ **/
+static void emit_build_progress(const struct file_list *flist)
+{
+	rprintf(FINFO, " %d files...\r", flist->count);
+}
+
+
+static void finish_build_progress(const struct file_list *flist)
+{
+	if (verbose && recurse && !am_server) {
+		/* This overwrites the progress line, if any. */
+		rprintf(FINFO, RSYNC_NAME ": %d files to consider.\n",
+			flist->count);
+	}
+}
+
+
+void show_flist_stats(void)
+{
+	/* Nothing yet */
+}
+
+
 static struct string_area *string_area_new(int size)
 {
 	struct string_area *a;
 
-	if (size <= 0) size = ARENA_SIZE;
+	if (size <= 0)
+		size = ARENA_SIZE;
 	a = malloc(sizeof(*a));
-	if (!a) out_of_memory("string_area_new");
+	if (!a)
+		out_of_memory("string_area_new");
 	a->current = a->base = malloc(size);
-	if (!a->current) out_of_memory("string_area_new buffer");
+	if (!a->current)
+		out_of_memory("string_area_new buffer");
 	a->end = a->base + size;
 	a->next = NULL;
 
 	return a;
 }
 
 static void string_area_free(struct string_area *a)
 {
 	struct string_area *next;
 
-	for ( ; a ; a = next) {
+	for (; a; a = next) {
 		next = a->next;
 		free(a->base);
 	}
 }
 
 static char *string_area_malloc(struct string_area **ap, int size)
