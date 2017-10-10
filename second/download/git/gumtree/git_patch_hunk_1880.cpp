 		goto rollback;
 	}
 
 	return 0;
 
  rollback:
-	lock = lock_ref_sha1_basic(oldrefname, NULL, 0, NULL);
+	lock = lock_ref_sha1_basic(oldrefname, NULL, NULL, 0, NULL);
 	if (!lock) {
 		error("unable to lock %s for rollback", oldrefname);
 		goto rollbacklog;
 	}
 
 	lock->force_write = 1;
