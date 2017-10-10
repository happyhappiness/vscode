 
 	if (!match_patterns(cb->pattern, refname))
 		return 0;
 
 	commit = NULL;
 	if (ref_list->verbose || ref_list->with_commit || merge_filter != NO_FILTER) {
-		commit = lookup_commit_reference_gently(sha1, 1);
+		commit = lookup_commit_reference_gently(oid->hash, 1);
 		if (!commit) {
 			cb->ret = error(_("branch '%s' does not point at a commit"), refname);
 			return 0;
 		}
 
 		/* Filter with with_commit if specified */
