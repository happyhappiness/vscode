 	static struct lock_file reflog_lock;
 	struct expire_reflog_cb cb;
 	struct ref_lock *lock;
 	char *log_file;
 	int status = 0;
 	int type;
+	struct strbuf err = STRBUF_INIT;
 
 	memset(&cb, 0, sizeof(cb));
 	cb.flags = flags;
 	cb.policy_cb = policy_cb_data;
 	cb.should_prune_fn = should_prune_fn;
 
 	/*
 	 * The reflog file is locked by holding the lock on the
 	 * reference itself, plus we might need to update the
 	 * reference if --updateref was specified:
 	 */
-	lock = lock_ref_sha1_basic(refname, sha1, NULL, 0, &type);
-	if (!lock)
-		return error("cannot lock ref '%s'", refname);
+	lock = lock_ref_sha1_basic(refname, sha1, NULL, NULL, 0, &type, &err);
+	if (!lock) {
+		error("cannot lock ref '%s': %s", refname, err.buf);
+		strbuf_release(&err);
+		return -1;
+	}
 	if (!reflog_exists(refname)) {
 		unlock_ref(lock);
 		return 0;
 	}
 
 	log_file = git_pathdup("logs/%s", refname);
