 	}
 
 	if (all)
 		checkout_all(prefix, prefix_length);
 
 	if (0 <= newfd &&
-	    (write_cache(newfd, active_cache, active_nr) ||
-	     commit_locked_index(&lock_file)))
+	    write_locked_index(&the_index, &lock_file, COMMIT_LOCK))
 		die("Unable to write new index file");
 	return 0;
 }
