 	   quiet, hash_only, abbrev, exclude_arg;
 static const char **pattern;
 static const char *exclude_existing_arg;
 
 static void show_one(const char *refname, const struct object_id *oid)
 {
-	const char *hex = find_unique_abbrev(oid->hash, abbrev);
+	const char *hex;
+	struct object_id peeled;
+
+	if (!has_sha1_file(oid->hash))
+		die("git show-ref: bad ref %s (%s)", refname,
+		    oid_to_hex(oid));
+
+	if (quiet)
+		return;
+
+	hex = find_unique_abbrev(oid->hash, abbrev);
 	if (hash_only)
 		printf("%s\n", hex);
 	else
 		printf("%s %s\n", hex, refname);
+
+	if (!deref_tags)
+		return;
+
+	if (!peel_ref(refname, peeled.hash)) {
+		hex = find_unique_abbrev(peeled.hash, abbrev);
+		printf("%s %s^{}\n", hex, refname);
+	}
 }
 
 static int show_ref(const char *refname, const struct object_id *oid,
 		    int flag, void *cbdata)
 {
-	const char *hex;
-	struct object_id peeled;
-
 	if (show_head && !strcmp(refname, "HEAD"))
 		goto match;
 
 	if (tags_only || heads_only) {
 		int match;
 
