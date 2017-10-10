 			if (reset_type == KEEP && !err)
 				err = reset_index(sha1, MIXED, quiet);
 			if (err)
 				die(_("Could not reset index file to revision '%s'."), rev);
 		}
 
-		if (write_cache(newfd, active_cache, active_nr) ||
-		    commit_locked_index(lock))
+		if (write_locked_index(&the_index, lock, COMMIT_LOCK))
 			die(_("Could not write new index file."));
 	}
 
 	if (!pathspec.nr && !unborn) {
 		/* Any resets without paths update HEAD to the head being
 		 * switched to, saving the previous head in ORIG_HEAD before. */
