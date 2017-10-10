 			return error(_("\nYou have uncommitted changes in your "
 				       "working tree. Please, commit them\n"
 				       "first and then run 'git rebase "
 				       "--continue' again."));
 
 		strbuf_release(&rev);
-		amend = 1;
+		flags |= AMEND_MSG;
 	}
 
-	if (run_git_commit(rebase_path_message(), opts, 1, 1, amend, 0))
+	if (run_git_commit(rebase_path_message(), opts, flags))
 		return error(_("could not commit staged changes."));
 	unlink(rebase_path_amend());
 	return 0;
 }
 
 int sequencer_continue(struct replay_opts *opts)
