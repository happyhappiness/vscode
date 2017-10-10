 	 * appear in the output before it is renamed (e.g., when a file
 	 * was copied and renamed in the same commit).
 	 */
 	return (a->status == 'R') - (b->status == 'R');
 }
 
-static void print_path(const char *path)
+static void print_path_1(const char *path)
 {
 	int need_quote = quote_c_style(path, NULL, NULL, 0);
 	if (need_quote)
 		quote_c_style(path, NULL, stdout, 0);
 	else if (strchr(path, ' '))
 		printf("\"%s\"", path);
 	else
 		printf("%s", path);
 }
 
+static void *anonymize_path_component(const void *path, size_t *len)
+{
+	static int counter;
+	struct strbuf out = STRBUF_INIT;
+	strbuf_addf(&out, "path%d", counter++);
+	return strbuf_detach(&out, len);
+}
+
+static void print_path(const char *path)
+{
+	if (!anonymize)
+		print_path_1(path);
+	else {
+		static struct hashmap paths;
+		static struct strbuf anon = STRBUF_INIT;
+
+		anonymize_path(&anon, path, &paths, anonymize_path_component);
+		print_path_1(anon.buf);
+		strbuf_reset(&anon);
+	}
+}
+
+static void *generate_fake_sha1(const void *old, size_t *len)
+{
+	static uint32_t counter = 1; /* avoid null sha1 */
+	unsigned char *out = xcalloc(20, 1);
+	put_be32(out + 16, counter++);
+	return out;
+}
+
+static const unsigned char *anonymize_sha1(const unsigned char *sha1)
+{
+	static struct hashmap sha1s;
+	size_t len = 20;
+	return anonymize_mem(&sha1s, generate_fake_sha1, sha1, &len);
+}
+
 static void show_filemodify(struct diff_queue_struct *q,
 			    struct diff_options *options, void *data)
 {
 	int i;
 
 	/*
