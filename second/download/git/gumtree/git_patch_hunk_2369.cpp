 		int save_errno = errno;
 		error("Couldn't write %s", lock->lk->filename.buf);
 		unlock_ref(lock);
 		errno = save_errno;
 		return -1;
 	}
+	return 0;
+}
+
+/*
+ * Commit a change to a loose reference that has already been written
+ * to the loose reference lockfile. Also update the reflogs if
+ * necessary, using the specified lockmsg (which can be NULL).
+ */
+static int commit_ref_update(struct ref_lock *lock,
+			     const unsigned char *sha1, const char *logmsg)
+{
 	clear_loose_ref_cache(&ref_cache);
 	if (log_ref_write(lock->ref_name, lock->old_sha1, sha1, logmsg) < 0 ||
 	    (strcmp(lock->ref_name, lock->orig_ref_name) &&
 	     log_ref_write(lock->orig_ref_name, lock->old_sha1, sha1, logmsg) < 0)) {
 		unlock_ref(lock);
 		return -1;
