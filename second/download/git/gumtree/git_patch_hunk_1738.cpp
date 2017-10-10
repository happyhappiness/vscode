 			rename_cache_entry_at(pos, dst);
 	}
 
 	if (gitmodules_modified)
 		stage_updated_gitmodules();
 
-	if (active_cache_changed) {
-		if (write_locked_index(&the_index, &lock_file, COMMIT_LOCK))
-			die(_("Unable to write new index file"));
-	}
+	if (active_cache_changed &&
+	    write_locked_index(&the_index, &lock_file, COMMIT_LOCK))
+		die(_("Unable to write new index file"));
 
 	return 0;
 }
