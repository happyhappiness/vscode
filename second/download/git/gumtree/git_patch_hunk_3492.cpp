 	 * The caller should run hooks on the locked real index, and
 	 * (A) if all goes well, commit the real index;
 	 * (B) on failure, rollback the real index.
 	 */
 	if (all || (also && pathspec.nr)) {
 		hold_locked_index(&index_lock, 1);
-		add_files_to_cache(also ? prefix : NULL, &pathspec, 0);
+		add_files_to_cache(also ? prefix : NULL, &pathspec, 0, 0);
 		refresh_cache_or_die(refresh_flags);
 		update_main_cache_tree(WRITE_TREE_SILENT);
 		if (write_locked_index(&the_index, &index_lock, CLOSE_LOCK))
 			die(_("unable to write new_index file"));
 		commit_style = COMMIT_NORMAL;
 		return get_lock_file_path(&index_lock);
