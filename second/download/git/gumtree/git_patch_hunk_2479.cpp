 	return best;
 }
 
 static int register_ref(const char *refname, const struct object_id *oid,
 			int flags, void *cb_data)
 {
-	if (!strcmp(refname, "bad")) {
+	struct strbuf good_prefix = STRBUF_INIT;
+	strbuf_addstr(&good_prefix, term_good);
+	strbuf_addstr(&good_prefix, "-");
+
+	if (!strcmp(refname, term_bad)) {
 		current_bad_oid = xmalloc(sizeof(*current_bad_oid));
 		oidcpy(current_bad_oid, oid);
-	} else if (starts_with(refname, "good-")) {
+	} else if (starts_with(refname, good_prefix.buf)) {
 		sha1_array_append(&good_revs, oid->hash);
 	} else if (starts_with(refname, "skip-")) {
 		sha1_array_append(&skipped_revs, oid->hash);
 	}
 
+	strbuf_release(&good_prefix);
+
 	return 0;
 }
 
 static int read_bisect_refs(void)
 {
 	return for_each_ref_in("refs/bisect/", register_ref, NULL);
 }
 
+static GIT_PATH_FUNC(git_path_bisect_names, "BISECT_NAMES")
+static GIT_PATH_FUNC(git_path_bisect_expected_rev, "BISECT_EXPECTED_REV")
+
 static void read_bisect_paths(struct argv_array *array)
 {
 	struct strbuf str = STRBUF_INIT;
-	const char *filename = git_path("BISECT_NAMES");
+	const char *filename = git_path_bisect_names();
 	FILE *fp = fopen(filename, "r");
 
 	if (!fp)
 		die_errno("Could not open file '%s'", filename);
 
 	while (strbuf_getline(&str, fp, '\n') != EOF) {
