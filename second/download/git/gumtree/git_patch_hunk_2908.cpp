 const void *get_commit_buffer(const struct commit *commit, unsigned long *sizep)
 {
 	const void *ret = get_cached_commit_buffer(commit, sizep);
 	if (!ret) {
 		enum object_type type;
 		unsigned long size;
-		ret = read_sha1_file(commit->object.sha1, &type, &size);
+		ret = read_sha1_file(commit->object.oid.hash, &type, &size);
 		if (!ret)
 			die("cannot read commit object %s",
-			    sha1_to_hex(commit->object.sha1));
+			    oid_to_hex(&commit->object.oid));
 		if (type != OBJ_COMMIT)
 			die("expected commit for %s, got %s",
-			    sha1_to_hex(commit->object.sha1), typename(type));
+			    oid_to_hex(&commit->object.oid), typename(type));
 		if (sizep)
 			*sizep = size;
 	}
 	return ret;
 }
 
