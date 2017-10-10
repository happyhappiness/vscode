 	 * hasn't asked for _all_ unreachable objects. If you have
 	 * deleted a branch by mistake, this is a prime candidate to
 	 * start looking at, for example.
 	 */
 	if (!obj->used) {
 		if (show_dangling)
-			printf("dangling %s %s\n", typename(obj->type),
+			printf("dangling %s %s\n", printable_type(obj),
 			       describe_object(obj));
 		if (write_lost_and_found) {
 			char *filename = git_pathdup("lost-found/%s/%s",
 				obj->type == OBJ_COMMIT ? "commit" : "other",
 				describe_object(obj));
 			FILE *f;
