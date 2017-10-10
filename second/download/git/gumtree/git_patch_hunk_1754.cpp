 		} else if (cmd->updateref &&
 			(write_in_full(lock->lock_fd,
 				sha1_to_hex(cb.last_kept_sha1), 40) != 40 ||
 			 write_str_in_full(lock->lock_fd, "\n") != 1 ||
 			 close_ref(lock) < 0)) {
 			status |= error("Couldn't write %s",
-				lock->lk->filename);
+					lock->lk->filename.buf);
 			unlink(newlog_path);
 		} else if (rename(newlog_path, log_file)) {
 			status |= error("cannot rename %s to %s",
 					newlog_path, log_file);
 			unlink(newlog_path);
 		} else if (cmd->updateref && commit_ref(lock)) {
