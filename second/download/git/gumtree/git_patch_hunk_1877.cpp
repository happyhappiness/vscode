 		if (remove_entry(packed, ref_to_delete->string) == -1)
 			die("internal error");
 	}
 
 	/* Write what remains */
 	ret = commit_packed_refs();
-	if (ret && err)
+	if (ret)
 		strbuf_addf(err, "unable to overwrite old ref-pack file: %s",
 			    strerror(errno));
 	return ret;
 }
 
-static int repack_without_ref(const char *refname)
+static int delete_ref_loose(struct ref_lock *lock, int flag, struct strbuf *err)
 {
-	return repack_without_refs(&refname, 1, NULL);
-}
+	assert(err);
 
-static int delete_ref_loose(struct ref_lock *lock, int flag)
-{
 	if (!(flag & REF_ISPACKED) || flag & REF_ISSYMREF) {
-		/* loose */
-		int err, i = strlen(lock->lk->filename) - 5; /* .lock */
-
-		lock->lk->filename[i] = 0;
-		err = unlink_or_warn(lock->lk->filename);
-		lock->lk->filename[i] = '.';
-		if (err && errno != ENOENT)
+		/*
+		 * loose.  The loose file name is the same as the
+		 * lockfile name, minus ".lock":
+		 */
+		char *loose_filename = get_locked_file_path(lock->lk);
+		int res = unlink_or_msg(loose_filename, err);
+		free(loose_filename);
+		if (res)
 			return 1;
 	}
 	return 0;
 }
 
 int delete_ref(const char *refname, const unsigned char *sha1, int delopt)
 {
-	struct ref_lock *lock;
-	int ret = 0, flag = 0;
+	struct ref_transaction *transaction;
+	struct strbuf err = STRBUF_INIT;
 
-	lock = lock_ref_sha1_basic(refname, sha1, delopt, &flag);
-	if (!lock)
+	transaction = ref_transaction_begin(&err);
+	if (!transaction ||
+	    ref_transaction_delete(transaction, refname, sha1, delopt,
+				   sha1 && !is_null_sha1(sha1), NULL, &err) ||
+	    ref_transaction_commit(transaction, &err)) {
+		error("%s", err.buf);
+		ref_transaction_free(transaction);
+		strbuf_release(&err);
 		return 1;
-	ret |= delete_ref_loose(lock, flag);
-
-	/* removing the loose one could have resurrected an earlier
-	 * packed one.  Also, if it was not loose we need to repack
-	 * without it.
-	 */
-	ret |= repack_without_ref(lock->ref_name);
-
-	unlink_or_warn(git_path("logs/%s", lock->ref_name));
-	clear_loose_ref_cache(&ref_cache);
-	unlock_ref(lock);
-	return ret;
+	}
+	ref_transaction_free(transaction);
+	strbuf_release(&err);
+	return 0;
 }
 
 /*
  * People using contrib's git-new-workdir have .git/logs/refs ->
  * /some/other/path/.git/logs/refs, and that may live on another device.
  *
