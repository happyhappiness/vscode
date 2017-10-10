 	 * deleted a branch by mistake, this is a prime candidate to
 	 * start looking at, for example.
 	 */
 	if (!obj->used) {
 		if (show_dangling)
 			printf("dangling %s %s\n", typename(obj->type),
-			       oid_to_hex(&obj->oid));
+			       describe_object(obj));
 		if (write_lost_and_found) {
 			char *filename = git_pathdup("lost-found/%s/%s",
 				obj->type == OBJ_COMMIT ? "commit" : "other",
-				oid_to_hex(&obj->oid));
+				describe_object(obj));
 			FILE *f;
 
 			if (safe_create_leading_directories_const(filename)) {
 				error("Could not create lost-found");
 				free(filename);
 				return;
