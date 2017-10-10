 	}
 
 	rf->merge = no_merged
 		? REF_FILTER_MERGED_OMIT
 		: REF_FILTER_MERGED_INCLUDE;
 
-	if (get_sha1(arg, sha1))
+	if (get_oid(arg, &oid))
 		die(_("malformed object name %s"), arg);
 
-	rf->merge_commit = lookup_commit_reference_gently(sha1, 0);
+	rf->merge_commit = lookup_commit_reference_gently(&oid, 0);
 	if (!rf->merge_commit)
 		return opterror(opt, "must point to a commit", 0);
 
 	return 0;
 }
