 		add_files_to_cache(also ? prefix : NULL, &pathspec, 0);
 		refresh_cache_or_die(refresh_flags);
 		update_main_cache_tree(WRITE_TREE_SILENT);
 		if (write_locked_index(&the_index, &index_lock, CLOSE_LOCK))
 			die(_("unable to write new_index file"));
 		commit_style = COMMIT_NORMAL;
-		return index_lock.filename;
+		return index_lock.filename.buf;
 	}
 
 	/*
 	 * As-is commit.
 	 *
 	 * (1) return the name of the real index file.
