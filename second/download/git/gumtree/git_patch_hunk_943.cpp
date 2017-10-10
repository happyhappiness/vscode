 		printf("Removing stale temporary file %s\n", fullpath);
 	if (!show_only)
 		unlink_or_warn(fullpath);
 	return 0;
 }
 
-static int prune_object(const unsigned char *sha1, const char *fullpath,
+static int prune_object(const struct object_id *oid, const char *fullpath,
 			void *data)
 {
 	struct stat st;
 
 	/*
 	 * Do we know about this object?
 	 * It must have been reachable
 	 */
-	if (lookup_object(sha1))
+	if (lookup_object(oid->hash))
 		return 0;
 
 	if (lstat(fullpath, &st)) {
 		/* report errors, but do not stop pruning */
 		error("Could not stat '%s'", fullpath);
 		return 0;
 	}
 	if (st.st_mtime > expire)
 		return 0;
 	if (show_only || verbose) {
-		enum object_type type = sha1_object_info(sha1, NULL);
-		printf("%s %s\n", sha1_to_hex(sha1),
+		enum object_type type = sha1_object_info(oid->hash, NULL);
+		printf("%s %s\n", oid_to_hex(oid),
 		       (type > 0) ? typename(type) : "unknown");
 	}
 	if (!show_only)
 		unlink_or_warn(fullpath);
 	return 0;
 }
