 
 	if (reset_type != SOFT) {
 		struct lock_file *lock = xcalloc(1, sizeof(*lock));
 		hold_locked_index(lock, 1);
 		if (reset_type == MIXED) {
 			int flags = quiet ? REFRESH_QUIET : REFRESH_IN_PORCELAIN;
-			if (read_from_tree(&pathspec, oid.hash, intent_to_add))
+			if (read_from_tree(&pathspec, &oid, intent_to_add))
 				return 1;
 			if (get_git_work_tree())
 				refresh_index(&the_index, flags, NULL, NULL,
 					      _("Unstaged changes after reset:"));
 		} else {
-			int err = reset_index(oid.hash, reset_type, quiet);
+			int err = reset_index(&oid, reset_type, quiet);
 			if (reset_type == KEEP && !err)
-				err = reset_index(oid.hash, MIXED, quiet);
+				err = reset_index(&oid, MIXED, quiet);
 			if (err)
 				die(_("Could not reset index file to revision '%s'."), rev);
 		}
 
 		if (write_locked_index(&the_index, lock, COMMIT_LOCK))
 			die(_("Could not write new index file."));
 	}
 
 	if (!pathspec.nr && !unborn) {
 		/* Any resets without paths update HEAD to the head being
 		 * switched to, saving the previous head in ORIG_HEAD before. */
-		update_ref_status = reset_refs(rev, oid.hash);
+		update_ref_status = reset_refs(rev, &oid);
 
 		if (reset_type == HARD && !update_ref_status && !quiet)
 			print_new_head_line(lookup_commit_reference(oid.hash));
 	}
 	if (!pathspec.nr)
 		remove_branch_state();
