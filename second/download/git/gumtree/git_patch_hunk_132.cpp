 			free((char *)p);
 		}
 		strbuf_release(&nbuf);
 		strbuf_release(&buf);
 	}
 
+	if (split_index > 0) {
+		init_split_index(&the_index);
+		the_index.cache_changed |= SPLIT_INDEX_ORDERED;
+	} else if (!split_index && the_index.split_index) {
+		/*
+		 * can't discard_split_index(&the_index); because that
+		 * will destroy split_index->base->cache[], which may
+		 * be shared with the_index.cache[]. So yeah we're
+		 * leaking a bit here.
+		 */
+		the_index.split_index = NULL;
+		the_index.cache_changed |= SOMETHING_CHANGED;
+	}
+
 	if (active_cache_changed) {
 		if (newfd < 0) {
 			if (refresh_args.flags & REFRESH_QUIET)
 				exit(128);
 			unable_to_lock_index_die(get_index_file(), lock_error);
 		}
-		if (write_cache(newfd, active_cache, active_nr) ||
-		    commit_locked_index(lock_file))
+		if (write_locked_index(&the_index, lock_file, COMMIT_LOCK))
 			die("Unable to write new index file");
 	}
 
 	rollback_lock_file(lock_file);
 
 	return has_errors ? 1 : 0;
