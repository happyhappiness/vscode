 		if (is_null_sha1(head_sha1))
 			return error("Unable to resolve remote HEAD");
 		if (!has_sha1_file(head_sha1))
 			return error("Remote HEAD resolves to object %s\nwhich does not exist locally, perhaps you need to fetch?", sha1_to_hex(head_sha1));
 
 		/* Remote branch must resolve to a known object */
-		if (is_null_sha1(remote_ref->old_sha1))
+		if (is_null_oid(&remote_ref->old_oid))
 			return error("Unable to resolve remote branch %s",
 				     remote_ref->name);
-		if (!has_sha1_file(remote_ref->old_sha1))
-			return error("Remote branch %s resolves to object %s\nwhich does not exist locally, perhaps you need to fetch?", remote_ref->name, sha1_to_hex(remote_ref->old_sha1));
+		if (!has_object_file(&remote_ref->old_oid))
+			return error("Remote branch %s resolves to object %s\nwhich does not exist locally, perhaps you need to fetch?", remote_ref->name, oid_to_hex(&remote_ref->old_oid));
 
 		/* Remote branch must be an ancestor of remote HEAD */
 		if (!verify_merge_base(head_sha1, remote_ref)) {
 			return error("The branch '%s' is not an ancestor "
 				     "of your current HEAD.\n"
 				     "If you are sure you want to delete it,"
