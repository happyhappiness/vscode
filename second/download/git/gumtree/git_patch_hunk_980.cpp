 				const unsigned char *sha1, const void *cb_data);
 
 static int for_each_tag_name(const char **argv, each_tag_name_fn fn,
 			     const void *cb_data)
 {
 	const char **p;
-	char ref[PATH_MAX];
+	struct strbuf ref = STRBUF_INIT;
 	int had_error = 0;
 	unsigned char sha1[20];
 
 	for (p = argv; *p; p++) {
-		if (snprintf(ref, sizeof(ref), "refs/tags/%s", *p)
-					>= sizeof(ref)) {
-			error(_("tag name too long: %.*s..."), 50, *p);
-			had_error = 1;
-			continue;
-		}
-		if (read_ref(ref, sha1)) {
+		strbuf_reset(&ref);
+		strbuf_addf(&ref, "refs/tags/%s", *p);
+		if (read_ref(ref.buf, sha1)) {
 			error(_("tag '%s' not found."), *p);
 			had_error = 1;
 			continue;
 		}
-		if (fn(*p, ref, sha1, cb_data))
+		if (fn(*p, ref.buf, sha1, cb_data))
 			had_error = 1;
 	}
+	strbuf_release(&ref);
 	return had_error;
 }
 
 static int delete_tag(const char *name, const char *ref,
 		      const unsigned char *sha1, const void *cb_data)
 {
-	if (delete_ref(ref, sha1, 0))
+	if (delete_ref(NULL, ref, sha1, 0))
 		return 1;
 	printf(_("Deleted tag '%s' (was %s)\n"), name, find_unique_abbrev(sha1, DEFAULT_ABBREV));
 	return 0;
 }
 
 static int verify_tag(const char *name, const char *ref,
