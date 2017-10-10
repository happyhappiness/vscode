 	struct commit commit;
 	struct tag tag;
 };
 
 DEFINE_ALLOCATOR(blob, struct blob)
 DEFINE_ALLOCATOR(tree, struct tree)
-DEFINE_ALLOCATOR(commit, struct commit)
+DEFINE_ALLOCATOR(raw_commit, struct commit)
 DEFINE_ALLOCATOR(tag, struct tag)
 DEFINE_ALLOCATOR(object, union any_object)
 
+void *alloc_commit_node(void)
+{
+	static int commit_count;
+	struct commit *c = alloc_raw_commit_node();
+	c->index = commit_count++;
+	return c;
+}
+
 static void report(const char *name, unsigned int count, size_t size)
 {
 	fprintf(stderr, "%10s: %8u (%"PRIuMAX" kB)\n",
 			name, count, (uintmax_t) size);
 }
 
-#define REPORT(name)	\
-    report(#name, name##_allocs, name##_allocs * sizeof(struct name) >> 10)
+#define REPORT(name, type)	\
+    report(#name, name##_allocs, name##_allocs * sizeof(type) >> 10)
 
 void alloc_report(void)
 {
-	REPORT(blob);
-	REPORT(tree);
-	REPORT(commit);
-	REPORT(tag);
+	REPORT(blob, struct blob);
+	REPORT(tree, struct tree);
+	REPORT(raw_commit, struct commit);
+	REPORT(tag, struct tag);
+	REPORT(object, union any_object);
 }
