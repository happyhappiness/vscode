 		}
 		string_list_append(hide_refs, ref);
 	}
 	return 0;
 }
 
-int ref_is_hidden(const char *refname)
+int ref_is_hidden(const char *refname, const char *refname_full)
 {
 	int i;
 
 	if (!hide_refs)
 		return 0;
 	for (i = hide_refs->nr - 1; i >= 0; i--) {
 		const char *match = hide_refs->items[i].string;
+		const char *subject;
 		int neg = 0;
 		int len;
 
 		if (*match == '!') {
 			neg = 1;
 			match++;
 		}
 
-		if (!starts_with(refname, match))
+		if (*match == '^') {
+			subject = refname_full;
+			match++;
+		} else {
+			subject = refname;
+		}
+
+		/* refname can be NULL when namespaces are used. */
+		if (!subject || !starts_with(subject, match))
 			continue;
 		len = strlen(match);
-		if (!refname[len] || refname[len] == '/')
+		if (!subject[len] || subject[len] == '/')
 			return !neg;
 	}
 	return 0;
 }
 
-struct expire_reflog_cb {
-	unsigned int flags;
-	reflog_expiry_should_prune_fn *should_prune_fn;
-	void *policy_cb;
-	FILE *newlog;
-	unsigned char last_kept_sha1[20];
-};
+const char *find_descendant_ref(const char *dirname,
+				const struct string_list *extras,
+				const struct string_list *skip)
+{
+	int pos;
 
-static int expire_reflog_ent(unsigned char *osha1, unsigned char *nsha1,
-			     const char *email, unsigned long timestamp, int tz,
-			     const char *message, void *cb_data)
-{
-	struct expire_reflog_cb *cb = cb_data;
-	struct expire_reflog_policy_cb *policy_cb = cb->policy_cb;
-
-	if (cb->flags & EXPIRE_REFLOGS_REWRITE)
-		osha1 = cb->last_kept_sha1;
-
-	if ((*cb->should_prune_fn)(osha1, nsha1, email, timestamp, tz,
-				   message, policy_cb)) {
-		if (!cb->newlog)
-			printf("would prune %s", message);
-		else if (cb->flags & EXPIRE_REFLOGS_VERBOSE)
-			printf("prune %s", message);
-	} else {
-		if (cb->newlog) {
-			fprintf(cb->newlog, "%s %s %s %lu %+05d\t%s",
-				sha1_to_hex(osha1), sha1_to_hex(nsha1),
-				email, timestamp, tz, message);
-			hashcpy(cb->last_kept_sha1, nsha1);
-		}
-		if (cb->flags & EXPIRE_REFLOGS_VERBOSE)
-			printf("keep %s", message);
-	}
-	return 0;
-}
+	if (!extras)
+		return NULL;
 
-int reflog_expire(const char *refname, const unsigned char *sha1,
-		 unsigned int flags,
-		 reflog_expiry_prepare_fn prepare_fn,
-		 reflog_expiry_should_prune_fn should_prune_fn,
-		 reflog_expiry_cleanup_fn cleanup_fn,
-		 void *policy_cb_data)
-{
-	static struct lock_file reflog_lock;
-	struct expire_reflog_cb cb;
-	struct ref_lock *lock;
-	char *log_file;
-	int status = 0;
-	int type;
-	struct strbuf err = STRBUF_INIT;
+	/*
+	 * Look at the place where dirname would be inserted into
+	 * extras. If there is an entry at that position that starts
+	 * with dirname (remember, dirname includes the trailing
+	 * slash) and is not in skip, then we have a conflict.
+	 */
+	for (pos = string_list_find_insert_index(extras, dirname, 0);
+	     pos < extras->nr; pos++) {
+		const char *extra_refname = extras->items[pos].string;
 
-	memset(&cb, 0, sizeof(cb));
-	cb.flags = flags;
-	cb.policy_cb = policy_cb_data;
-	cb.should_prune_fn = should_prune_fn;
+		if (!starts_with(extra_refname, dirname))
+			break;
 
-	/*
-	 * The reflog file is locked by holding the lock on the
-	 * reference itself, plus we might need to update the
-	 * reference if --updateref was specified:
-	 */
-	lock = lock_ref_sha1_basic(refname, sha1, NULL, NULL, 0, &type, &err);
-	if (!lock) {
-		error("cannot lock ref '%s': %s", refname, err.buf);
-		strbuf_release(&err);
-		return -1;
-	}
-	if (!reflog_exists(refname)) {
-		unlock_ref(lock);
-		return 0;
+		if (!skip || !string_list_has_string(skip, extra_refname))
+			return extra_refname;
 	}
+	return NULL;
+}
 
-	log_file = git_pathdup("logs/%s", refname);
-	if (!(flags & EXPIRE_REFLOGS_DRY_RUN)) {
-		/*
-		 * Even though holding $GIT_DIR/logs/$reflog.lock has
-		 * no locking implications, we use the lock_file
-		 * machinery here anyway because it does a lot of the
-		 * work we need, including cleaning up if the program
-		 * exits unexpectedly.
-		 */
-		if (hold_lock_file_for_update(&reflog_lock, log_file, 0) < 0) {
-			struct strbuf err = STRBUF_INIT;
-			unable_to_lock_message(log_file, errno, &err);
-			error("%s", err.buf);
-			strbuf_release(&err);
-			goto failure;
-		}
-		cb.newlog = fdopen_lock_file(&reflog_lock, "w");
-		if (!cb.newlog) {
-			error("cannot fdopen %s (%s)",
-			      get_lock_file_path(&reflog_lock), strerror(errno));
-			goto failure;
-		}
-	}
+int rename_ref_available(const char *oldname, const char *newname)
+{
+	struct string_list skip = STRING_LIST_INIT_NODUP;
+	struct strbuf err = STRBUF_INIT;
+	int ret;
 
-	(*prepare_fn)(refname, sha1, cb.policy_cb);
-	for_each_reflog_ent(refname, expire_reflog_ent, &cb);
-	(*cleanup_fn)(cb.policy_cb);
+	string_list_insert(&skip, oldname);
+	ret = !verify_refname_available(newname, NULL, &skip, &err);
+	if (!ret)
+		error("%s", err.buf);
 
-	if (!(flags & EXPIRE_REFLOGS_DRY_RUN)) {
-		/*
-		 * It doesn't make sense to adjust a reference pointed
-		 * to by a symbolic ref based on expiring entries in
-		 * the symbolic reference's reflog. Nor can we update
-		 * a reference if there are no remaining reflog
-		 * entries.
-		 */
-		int update = (flags & EXPIRE_REFLOGS_UPDATE_REF) &&
-			!(type & REF_ISSYMREF) &&
-			!is_null_sha1(cb.last_kept_sha1);
-
-		if (close_lock_file(&reflog_lock)) {
-			status |= error("couldn't write %s: %s", log_file,
-					strerror(errno));
-		} else if (update &&
-			   (write_in_full(get_lock_file_fd(lock->lk),
-				sha1_to_hex(cb.last_kept_sha1), 40) != 40 ||
-			    write_str_in_full(get_lock_file_fd(lock->lk), "\n") != 1 ||
-			    close_ref(lock) < 0)) {
-			status |= error("couldn't write %s",
-					get_lock_file_path(lock->lk));
-			rollback_lock_file(&reflog_lock);
-		} else if (commit_lock_file(&reflog_lock)) {
-			status |= error("unable to write reflog %s: %s",
-					log_file, strerror(errno));
-		} else if (update && commit_ref(lock)) {
-			status |= error("couldn't set %s", lock->ref_name);
-		}
-	}
-	free(log_file);
-	unlock_ref(lock);
-	return status;
-
- failure:
-	rollback_lock_file(&reflog_lock);
-	free(log_file);
-	unlock_ref(lock);
-	return -1;
+	string_list_clear(&skip, 0);
+	strbuf_release(&err);
+	return ret;
 }
