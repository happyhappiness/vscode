 
 	if (result >= 0) /* Merge resulted (trivially) in result_sha1 */
 		/* Update default notes ref with new commit */
 		update_ref(msg.buf, default_notes_ref(), result_sha1, NULL,
 			   0, UPDATE_REFS_DIE_ON_ERR);
 	else { /* Merge has unresolved conflicts */
-		char *existing;
+		const struct worktree *wt;
 		/* Update .git/NOTES_MERGE_PARTIAL with partial merge result */
 		update_ref(msg.buf, "NOTES_MERGE_PARTIAL", result_sha1, NULL,
 			   0, UPDATE_REFS_DIE_ON_ERR);
 		/* Store ref-to-be-updated into .git/NOTES_MERGE_REF */
-		existing = find_shared_symref("NOTES_MERGE_REF", default_notes_ref());
-		if (existing)
+		wt = find_shared_symref("NOTES_MERGE_REF", default_notes_ref());
+		if (wt)
 			die(_("A notes merge into %s is already in-progress at %s"),
-			    default_notes_ref(), existing);
+			    default_notes_ref(), wt->path);
 		if (create_symref("NOTES_MERGE_REF", default_notes_ref(), NULL))
 			die("Failed to store link to current notes ref (%s)",
 			    default_notes_ref());
 		printf("Automatic notes merge failed. Fix conflicts in %s and "
 		       "commit the result with 'git notes merge --commit', or "
 		       "abort the merge with 'git notes merge --abort'.\n",
