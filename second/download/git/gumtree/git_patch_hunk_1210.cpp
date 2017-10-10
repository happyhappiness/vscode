 	argv_show_branch[1] = bisect_rev_hex;
 	return run_command_v_opt(argv_show_branch, RUN_GIT_CMD);
 }
 
 static struct commit *get_commit_reference(const struct object_id *oid)
 {
-	struct commit *r = lookup_commit_reference(oid->hash);
+	struct commit *r = lookup_commit_reference(oid);
 	if (!r)
 		die(_("Not a valid commit name %s"), oid_to_hex(oid));
 	return r;
 }
 
 static struct commit **get_bad_and_good_commits(int *rev_nr)
