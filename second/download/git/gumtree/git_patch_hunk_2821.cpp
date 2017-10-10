 	/*
 	 * We obviously want the object to be parsed,
 	 * except if it was in a pack-file and we didn't
 	 * do a full fsck
 	 */
 	if (!(obj->flags & HAS_OBJ)) {
-		if (has_sha1_pack(obj->sha1))
+		if (has_sha1_pack(obj->oid.hash))
 			return; /* it is in pack - forget about it */
-		if (connectivity_only && has_sha1_file(obj->sha1))
+		if (connectivity_only && has_object_file(&obj->oid))
 			return;
-		printf("missing %s %s\n", typename(obj->type), sha1_to_hex(obj->sha1));
+		printf("missing %s %s\n", typename(obj->type), oid_to_hex(&obj->oid));
 		errors_found |= ERROR_REACHABLE;
 		return;
 	}
 }
 
 /*
