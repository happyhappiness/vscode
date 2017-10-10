 		/* Store ref-to-be-updated into .git/NOTES_MERGE_REF */
 		wt = find_shared_symref("NOTES_MERGE_REF", default_notes_ref());
 		if (wt)
 			die(_("A notes merge into %s is already in-progress at %s"),
 			    default_notes_ref(), wt->path);
 		if (create_symref("NOTES_MERGE_REF", default_notes_ref(), NULL))
-			die("Failed to store link to current notes ref (%s)",
+			die(_("Failed to store link to current notes ref (%s)"),
 			    default_notes_ref());
-		printf("Automatic notes merge failed. Fix conflicts in %s and "
-		       "commit the result with 'git notes merge --commit', or "
-		       "abort the merge with 'git notes merge --abort'.\n",
+		printf(_("Automatic notes merge failed. Fix conflicts in %s and "
+			 "commit the result with 'git notes merge --commit', or "
+			 "abort the merge with 'git notes merge --abort'.\n"),
 		       git_path(NOTES_MERGE_WORKTREE));
 	}
 
 	free_notes(t);
 	strbuf_release(&remote_ref);
 	strbuf_release(&msg);
