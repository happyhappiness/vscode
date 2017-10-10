 	struct commit *commit;
 	struct object_id commit_oid;
 
 	if (get_mail_commit_oid(&commit_oid, mail) < 0)
 		die(_("could not parse %s"), mail);
 
-	commit = lookup_commit_or_die(commit_oid.hash, mail);
+	commit = lookup_commit_or_die(&commit_oid, mail);
 
 	get_commit_info(state, commit);
 
 	write_commit_patch(state, commit);
 
 	oidcpy(&state->orig_commit, &commit_oid);
