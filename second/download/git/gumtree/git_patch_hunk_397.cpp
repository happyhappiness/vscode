 		/* Update .git/NOTES_MERGE_PARTIAL with partial merge result */
 		update_ref(msg.buf, "NOTES_MERGE_PARTIAL", result_sha1, NULL,
 			   0, UPDATE_REFS_DIE_ON_ERR);
 		/* Store ref-to-be-updated into .git/NOTES_MERGE_REF */
 		wt = find_shared_symref("NOTES_MERGE_REF", default_notes_ref());
 		if (wt)
-			die(_("A notes merge into %s is already in-progress at %s"),
+			die(_("a notes merge into %s is already in-progress at %s"),
 			    default_notes_ref(), wt->path);
 		if (create_symref("NOTES_MERGE_REF", default_notes_ref(), NULL))
-			die(_("Failed to store link to current notes ref (%s)"),
+			die(_("failed to store link to current notes ref (%s)"),
 			    default_notes_ref());
 		printf(_("Automatic notes merge failed. Fix conflicts in %s and "
 			 "commit the result with 'git notes merge --commit', or "
 			 "abort the merge with 'git notes merge --abort'.\n"),
 		       git_path(NOTES_MERGE_WORKTREE));
 	}
