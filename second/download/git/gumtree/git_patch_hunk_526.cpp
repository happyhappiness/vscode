 	if (clean < 0)
 		return clean;
 
 	if (active_cache_changed &&
 	    write_locked_index(&the_index, &index_lock, COMMIT_LOCK))
 		/* TRANSLATORS: %s will be "revert" or "cherry-pick" */
-		die(_("%s: Unable to write new index file"), action_name(opts));
+		return error(_("%s: Unable to write new index file"),
+			_(action_name(opts)));
 	rollback_lock_file(&index_lock);
 
 	if (opts->signoff)
 		append_signoff(msgbuf, 0, 0);
 
 	if (!clean)
