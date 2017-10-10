 			 * Maybe somebody just deleted one of the
 			 * directories leading to ref_file.  Try
 			 * again:
 			 */
 			goto retry;
 		else {
-			struct strbuf err = STRBUF_INIT;
-			unable_to_lock_message(ref_file, errno, &err);
-			error("%s", err.buf);
-			strbuf_release(&err);
+			unable_to_lock_message(ref_file, errno, err);
 			goto error_return;
 		}
 	}
 	return old_sha1 ? verify_lock(lock, old_sha1, mustexist) : lock;
 
  error_return:
