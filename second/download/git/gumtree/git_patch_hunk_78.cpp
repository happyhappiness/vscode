 					 writeout_error);
 			if (ret)
 				return ret;
 		}
 	}
 
-	if (write_cache(newfd, active_cache, active_nr) ||
-	    commit_locked_index(lock_file))
+	if (write_locked_index(&the_index, lock_file, COMMIT_LOCK))
 		die(_("unable to write new index file"));
 
 	if (!opts->force && !opts->quiet)
 		show_local_changes(&new->commit->object, &opts->diff_options);
 
 	return 0;
