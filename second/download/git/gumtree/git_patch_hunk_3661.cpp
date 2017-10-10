 							   rev.message_id);
 			}
 			gen_message_id(&rev, oid_to_hex(&commit->object.oid));
 		}
 
 		if (!use_stdout &&
-		    reopen_stdout(rev.numbered_files ? NULL : commit, NULL, &rev, quiet))
+		    open_next_file(rev.numbered_files ? NULL : commit, NULL, &rev, quiet))
 			die(_("Failed to create output files"));
 		shown = log_tree_commit(&rev, commit);
 		free_commit_buffer(commit);
 
 		/* We put one extra blank line between formatted
 		 * patches and this flag is used by log-tree code
