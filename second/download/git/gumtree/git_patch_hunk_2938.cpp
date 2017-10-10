 	}
 
 	/*
 	 * Fetch a copy of the object if it doesn't exist locally - it
 	 * may be required for updating server info later.
 	 */
-	if (repo->can_update_info_refs && !has_sha1_file(ref->old_sha1)) {
-		obj = lookup_unknown_object(ref->old_sha1);
+	if (repo->can_update_info_refs && !has_object_file(&ref->old_oid)) {
+		obj = lookup_unknown_object(ref->old_oid.hash);
 		if (obj) {
 			fprintf(stderr,	"  fetch %s for %s\n",
-				sha1_to_hex(ref->old_sha1), refname);
+				oid_to_hex(&ref->old_oid), refname);
 			add_fetch_request(obj);
 		}
 	}
 
 	ref->next = remote_refs;
 	remote_refs = ref;
