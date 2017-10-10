 	strbuf_release(&sb);
 }
 
 #define MERGE_WARNING(path, msg) \
 	warning("Failed to merge submodule %s (%s)", path, msg);
 
-int merge_submodule(unsigned char result[20], const char *path,
-		    const unsigned char base[20], const unsigned char a[20],
-		    const unsigned char b[20], int search)
+int merge_submodule(struct object_id *result, const char *path,
+		    const struct object_id *base, const struct object_id *a,
+		    const struct object_id *b, int search)
 {
 	struct commit *commit_base, *commit_a, *commit_b;
 	int parent_count;
 	struct object_array merges;
 
 	int i;
 
 	/* store a in result in case we fail */
-	hashcpy(result, a);
+	oidcpy(result, a);
 
 	/* we can not handle deletion conflicts */
-	if (is_null_sha1(base))
+	if (is_null_oid(base))
 		return 0;
-	if (is_null_sha1(a))
+	if (is_null_oid(a))
 		return 0;
-	if (is_null_sha1(b))
+	if (is_null_oid(b))
 		return 0;
 
 	if (add_submodule_odb(path)) {
 		MERGE_WARNING(path, "not checked out");
 		return 0;
 	}
