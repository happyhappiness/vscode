 		printf("unreachable %s %s\n", printable_type(obj),
 			describe_object(obj));
 		return;
 	}
 
 	/*
-	 * "!used" means that nothing at all points to it, including
+	 * "!USED" means that nothing at all points to it, including
 	 * other unreachable objects. In other words, it's the "tip"
 	 * of some set of unreachable objects, usually a commit that
 	 * got dropped.
 	 *
 	 * Such starting points are more interesting than some random
 	 * set of unreachable objects, so we show them even if the user
 	 * hasn't asked for _all_ unreachable objects. If you have
 	 * deleted a branch by mistake, this is a prime candidate to
 	 * start looking at, for example.
 	 */
-	if (!obj->used) {
+	if (!(obj->flags & USED)) {
 		if (show_dangling)
 			printf("dangling %s %s\n", printable_type(obj),
 			       describe_object(obj));
 		if (write_lost_and_found) {
 			char *filename = git_pathdup("lost-found/%s/%s",
 				obj->type == OBJ_COMMIT ? "commit" : "other",
