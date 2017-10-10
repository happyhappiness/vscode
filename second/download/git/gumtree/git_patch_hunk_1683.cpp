 	struct tree_desc t;
 	int err = 0;
 
 	if (option_no_checkout)
 		return 0;
 
-	head = resolve_refdup("HEAD", sha1, 1, NULL);
+	head = resolve_refdup("HEAD", RESOLVE_REF_READING, sha1, NULL);
 	if (!head) {
 		warning(_("remote HEAD refers to nonexistent ref, "
 			  "unable to checkout.\n"));
 		return 0;
 	}
 	if (!strcmp(head, "HEAD")) {
