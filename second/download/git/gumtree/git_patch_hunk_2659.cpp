 	munmap(map, mapsz);
 }
 
 void add_to_alternates_file(const char *reference)
 {
 	struct lock_file *lock = xcalloc(1, sizeof(struct lock_file));
-	int fd = hold_lock_file_for_append(lock, git_path("objects/info/alternates"), LOCK_DIE_ON_ERROR);
-	const char *alt = mkpath("%s\n", reference);
-	write_or_die(fd, alt, strlen(alt));
-	if (commit_lock_file(lock))
-		die("could not close alternates file");
-	if (alt_odb_tail)
-		link_alt_odb_entries(alt, strlen(alt), '\n', NULL, 0);
+	char *alts = git_pathdup("objects/info/alternates");
+	FILE *in, *out;
+
+	hold_lock_file_for_update(lock, alts, LOCK_DIE_ON_ERROR);
+	out = fdopen_lock_file(lock, "w");
+	if (!out)
+		die_errno("unable to fdopen alternates lockfile");
+
+	in = fopen(alts, "r");
+	if (in) {
+		struct strbuf line = STRBUF_INIT;
+		int found = 0;
+
+		while (strbuf_getline(&line, in, '\n') != EOF) {
+			if (!strcmp(reference, line.buf)) {
+				found = 1;
+				break;
+			}
+			fprintf_or_die(out, "%s\n", line.buf);
+		}
+
+		strbuf_release(&line);
+		fclose(in);
+
+		if (found) {
+			rollback_lock_file(lock);
+			lock = NULL;
+		}
+	}
+	else if (errno != ENOENT)
+		die_errno("unable to read alternates file");
+
+	if (lock) {
+		fprintf_or_die(out, "%s\n", reference);
+		if (commit_lock_file(lock))
+			die_errno("unable to move new alternates file into place");
+		if (alt_odb_tail)
+			link_alt_odb_entries(reference, strlen(reference), '\n', NULL, 0);
+	}
+	free(alts);
 }
 
 int foreach_alt_odb(alt_odb_fn fn, void *cb)
 {
 	struct alternate_object_database *ent;
 	int r = 0;
