 	lock = lock_ref_sha1_basic(newrefname, NULL, NULL, NULL, 0, NULL, &err);
 	if (!lock) {
 		error("unable to rename '%s' to '%s': %s", oldrefname, newrefname, err.buf);
 		strbuf_release(&err);
 		goto rollback;
 	}
-	hashcpy(lock->old_sha1, orig_sha1);
+	hashcpy(lock->old_oid.hash, orig_sha1);
 
 	if (write_ref_to_lockfile(lock, orig_sha1) ||
 	    commit_ref_update(lock, orig_sha1, logmsg)) {
 		error("unable to write current sha1 into %s", newrefname);
 		goto rollback;
 	}
