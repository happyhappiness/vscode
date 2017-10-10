 			!is_null_sha1(cb.last_kept_sha1);
 
 		if (close_lock_file(&reflog_lock)) {
 			status |= error("couldn't write %s: %s", log_file,
 					strerror(errno));
 		} else if (update &&
-			   (write_in_full(lock->lk->fd,
+			   (write_in_full(get_lock_file_fd(lock->lk),
 				sha1_to_hex(cb.last_kept_sha1), 40) != 40 ||
-			 write_str_in_full(lock->lk->fd, "\n") != 1 ||
-			 close_ref(lock) < 0)) {
+			    write_str_in_full(get_lock_file_fd(lock->lk), "\n") != 1 ||
+			    close_ref(lock) < 0)) {
 			status |= error("couldn't write %s",
-					lock->lk->filename.buf);
+					get_lock_file_path(lock->lk));
 			rollback_lock_file(&reflog_lock);
 		} else if (commit_lock_file(&reflog_lock)) {
 			status |= error("unable to commit reflog '%s' (%s)",
 					log_file, strerror(errno));
 		} else if (update && commit_ref(lock)) {
 			status |= error("couldn't set %s", lock->ref_name);
