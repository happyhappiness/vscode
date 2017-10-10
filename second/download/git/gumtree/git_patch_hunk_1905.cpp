 
 static int is_index_unchanged(void)
 {
 	unsigned char head_sha1[20];
 	struct commit *head_commit;
 
-	if (!resolve_ref_unsafe("HEAD", head_sha1, 1, NULL))
+	if (!resolve_ref_unsafe("HEAD", RESOLVE_REF_READING, head_sha1, NULL))
 		return error(_("Could not resolve HEAD commit\n"));
 
 	head_commit = lookup_commit(head_sha1);
 
 	/*
 	 * If head_commit is NULL, check_commit, called from
