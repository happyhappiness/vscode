 static struct commit_extra_header *read_commit_extra_header_lines(const char *buf, size_t len, const char **);
 
 int save_commit_buffer = 1;
 
 const char *commit_type = "commit";
 
-struct commit *lookup_commit_reference_gently(const unsigned char *sha1,
+struct commit *lookup_commit_reference_gently(const struct object_id *oid,
 					      int quiet)
 {
-	struct object *obj = deref_tag(parse_object(sha1), NULL, 0);
+	struct object *obj = deref_tag(parse_object(oid), NULL, 0);
 
 	if (!obj)
 		return NULL;
 	return object_as_type(obj, OBJ_COMMIT, quiet);
 }
 
-struct commit *lookup_commit_reference(const unsigned char *sha1)
+struct commit *lookup_commit_reference(const struct object_id *oid)
 {
-	return lookup_commit_reference_gently(sha1, 0);
+	return lookup_commit_reference_gently(oid, 0);
 }
 
-struct commit *lookup_commit_or_die(const unsigned char *sha1, const char *ref_name)
+struct commit *lookup_commit_or_die(const struct object_id *oid, const char *ref_name)
 {
-	struct commit *c = lookup_commit_reference(sha1);
+	struct commit *c = lookup_commit_reference(oid);
 	if (!c)
 		die(_("could not parse %s"), ref_name);
-	if (hashcmp(sha1, c->object.oid.hash)) {
+	if (oidcmp(oid, &c->object.oid)) {
 		warning(_("%s %s is not a commit!"),
-			ref_name, sha1_to_hex(sha1));
+			ref_name, oid_to_hex(oid));
 	}
 	return c;
 }
 
-struct commit *lookup_commit(const unsigned char *sha1)
+struct commit *lookup_commit(const struct object_id *oid)
 {
-	struct object *obj = lookup_object(sha1);
+	struct object *obj = lookup_object(oid->hash);
 	if (!obj)
-		return create_object(sha1, alloc_commit_node());
+		return create_object(oid->hash, alloc_commit_node());
 	return object_as_type(obj, OBJ_COMMIT, 0);
 }
 
 struct commit *lookup_commit_reference_by_name(const char *name)
 {
 	struct object_id oid;
 	struct commit *commit;
 
 	if (get_sha1_committish(name, oid.hash))
 		return NULL;
-	commit = lookup_commit_reference(oid.hash);
+	commit = lookup_commit_reference(&oid);
 	if (parse_commit(commit))
 		return NULL;
 	return commit;
 }
 
-static unsigned long parse_commit_date(const char *buf, const char *tail)
+static timestamp_t parse_commit_date(const char *buf, const char *tail)
 {
 	const char *dateptr;
 
 	if (buf + 6 >= tail)
 		return 0;
 	if (memcmp(buf, "author", 6))
