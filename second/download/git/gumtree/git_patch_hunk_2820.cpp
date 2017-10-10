 		objerror(parent, "wrong object type in link");
 
 	if (obj->flags & REACHABLE)
 		return 0;
 	obj->flags |= REACHABLE;
 	if (!(obj->flags & HAS_OBJ)) {
-		if (parent && !has_sha1_file(obj->sha1)) {
+		if (parent && !has_object_file(&obj->oid)) {
 			printf("broken link from %7s %s\n",
-				 typename(parent->type), sha1_to_hex(parent->sha1));
+				 typename(parent->type), oid_to_hex(&parent->oid));
 			printf("              to %7s %s\n",
-				 typename(obj->type), sha1_to_hex(obj->sha1));
+				 typename(obj->type), oid_to_hex(&obj->oid));
 			errors_found |= ERROR_REACHABLE;
 		}
 		return 1;
 	}
 
 	add_object_array(obj, NULL, &pending);
