 			die("could not read ref '%s'", pseudoref);
 		if (hashcmp(actual_old_sha1, old_sha1)) {
 			warning("Unexpected sha1 when deleting %s", pseudoref);
 			rollback_lock_file(&lock);
 			return -1;
 		}
-
-		unlink(filename);
-		rollback_lock_file(&lock);
-	} else {
-		unlink(filename);
-	}
-
-	return 0;
-}
-
-int delete_ref(const char *refname, const unsigned char *old_sha1,
-	       unsigned int flags)
-{
-	struct ref_transaction *transaction;
-	struct strbuf err = STRBUF_INIT;
-
-	if (ref_type(refname) == REF_TYPE_PSEUDOREF)
-		return delete_pseudoref(refname, old_sha1);
-
-	transaction = ref_transaction_begin(&err);
-	if (!transaction ||
-	    ref_transaction_delete(transaction, refname, old_sha1,
-				   flags, NULL, &err) ||
-	    ref_transaction_commit(transaction, &err)) {
-		error("%s", err.buf);
-		ref_transaction_free(transaction);
-		strbuf_release(&err);
-		return 1;
-	}
-	ref_transaction_free(transaction);
-	strbuf_release(&err);
-	return 0;
-}
-
-int delete_refs(struct string_list *refnames)
-{
-	struct strbuf err = STRBUF_INIT;
-	int i, result = 0;
-
-	if (!refnames->nr)
-		return 0;
-
-	result = repack_without_refs(refnames, &err);
-	if (result) {
-		/*
-		 * If we failed to rewrite the packed-refs file, then
-		 * it is unsafe to try to remove loose refs, because
-		 * doing so might expose an obsolete packed value for
-		 * a reference that might even point at an object that
-		 * has been garbage collected.
-		 */
-		if (refnames->nr == 1)
-			error(_("could not delete reference %s: %s"),
-			      refnames->items[0].string, err.buf);
-		else
-			error(_("could not delete references: %s"), err.buf);
-
-		goto out;
-	}
-
-	for (i = 0; i < refnames->nr; i++) {
-		const char *refname = refnames->items[i].string;
-
-		if (delete_ref(refname, NULL, 0))
-			result |= error(_("could not remove reference %s"), refname);
-	}
-
-out:
-	strbuf_release(&err);
-	return result;
-}
-
-/*
- * People using contrib's git-new-workdir have .git/logs/refs ->
- * /some/other/path/.git/logs/refs, and that may live on another device.
- *
- * IOW, to avoid cross device rename errors, the temporary renamed log must
- * live into logs/refs.
- */
-#define TMP_RENAMED_LOG  "logs/refs/.tmp-renamed-log"
-
-static int rename_tmp_log(const char *newrefname)
-{
-	int attempts_remaining = 4;
-	struct strbuf path = STRBUF_INIT;
-	int ret = -1;
-
- retry:
-	strbuf_reset(&path);
-	strbuf_git_path(&path, "logs/%s", newrefname);
-	switch (safe_create_leading_directories_const(path.buf)) {
-	case SCLD_OK:
-		break; /* success */
-	case SCLD_VANISHED:
-		if (--attempts_remaining > 0)
-			goto retry;
-		/* fall through */
-	default:
-		error("unable to create directory for %s", newrefname);
-		goto out;
-	}
-
-	if (rename(git_path(TMP_RENAMED_LOG), path.buf)) {
-		if ((errno==EISDIR || errno==ENOTDIR) && --attempts_remaining > 0) {
-			/*
-			 * rename(a, b) when b is an existing
-			 * directory ought to result in ISDIR, but
-			 * Solaris 5.8 gives ENOTDIR.  Sheesh.
-			 */
-			if (remove_empty_directories(&path)) {
-				error("Directory not empty: logs/%s", newrefname);
-				goto out;
-			}
-			goto retry;
-		} else if (errno == ENOENT && --attempts_remaining > 0) {
-			/*
-			 * Maybe another process just deleted one of
-			 * the directories in the path to newrefname.
-			 * Try again from the beginning.
-			 */
-			goto retry;
-		} else {
-			error("unable to move logfile "TMP_RENAMED_LOG" to logs/%s: %s",
-				newrefname, strerror(errno));
-			goto out;
-		}
-	}
-	ret = 0;
-out:
-	strbuf_release(&path);
-	return ret;
-}
-
-static int rename_ref_available(const char *oldname, const char *newname)
-{
-	struct string_list skip = STRING_LIST_INIT_NODUP;
-	struct strbuf err = STRBUF_INIT;
-	int ret;
-
-	string_list_insert(&skip, oldname);
-	ret = !verify_refname_available(newname, NULL, &skip,
-					get_packed_refs(&ref_cache), &err)
-		&& !verify_refname_available(newname, NULL, &skip,
-					     get_loose_refs(&ref_cache), &err);
-	if (!ret)
-		error("%s", err.buf);
-
-	string_list_clear(&skip, 0);
-	strbuf_release(&err);
-	return ret;
-}
-
-static int write_ref_to_lockfile(struct ref_lock *lock,
-				 const unsigned char *sha1, struct strbuf *err);
-static int commit_ref_update(struct ref_lock *lock,
-			     const unsigned char *sha1, const char *logmsg,
-			     int flags, struct strbuf *err);
-
-int rename_ref(const char *oldrefname, const char *newrefname, const char *logmsg)
-{
-	unsigned char sha1[20], orig_sha1[20];
-	int flag = 0, logmoved = 0;
-	struct ref_lock *lock;
-	struct stat loginfo;
-	int log = !lstat(git_path("logs/%s", oldrefname), &loginfo);
-	const char *symref = NULL;
-	struct strbuf err = STRBUF_INIT;
-
-	if (log && S_ISLNK(loginfo.st_mode))
-		return error("reflog for %s is a symlink", oldrefname);
-
-	symref = resolve_ref_unsafe(oldrefname, RESOLVE_REF_READING,
-				    orig_sha1, &flag);
-	if (flag & REF_ISSYMREF)
-		return error("refname %s is a symbolic ref, renaming it is not supported",
-			oldrefname);
-	if (!symref)
-		return error("refname %s not found", oldrefname);
-
-	if (!rename_ref_available(oldrefname, newrefname))
-		return 1;
-
-	if (log && rename(git_path("logs/%s", oldrefname), git_path(TMP_RENAMED_LOG)))
-		return error("unable to move logfile logs/%s to "TMP_RENAMED_LOG": %s",
-			oldrefname, strerror(errno));
-
-	if (delete_ref(oldrefname, orig_sha1, REF_NODEREF)) {
-		error("unable to delete old %s", oldrefname);
-		goto rollback;
-	}
-
-	if (!read_ref_full(newrefname, RESOLVE_REF_READING, sha1, NULL) &&
-	    delete_ref(newrefname, sha1, REF_NODEREF)) {
-		if (errno==EISDIR) {
-			struct strbuf path = STRBUF_INIT;
-			int result;
-
-			strbuf_git_path(&path, "%s", newrefname);
-			result = remove_empty_directories(&path);
-			strbuf_release(&path);
-
-			if (result) {
-				error("Directory not empty: %s", newrefname);
-				goto rollback;
-			}
-		} else {
-			error("unable to delete existing %s", newrefname);
-			goto rollback;
-		}
-	}
-
-	if (log && rename_tmp_log(newrefname))
-		goto rollback;
-
-	logmoved = log;
-
-	lock = lock_ref_sha1_basic(newrefname, NULL, NULL, NULL, 0, NULL, &err);
-	if (!lock) {
-		error("unable to rename '%s' to '%s': %s", oldrefname, newrefname, err.buf);
-		strbuf_release(&err);
-		goto rollback;
-	}
-	hashcpy(lock->old_oid.hash, orig_sha1);
-
-	if (write_ref_to_lockfile(lock, orig_sha1, &err) ||
-	    commit_ref_update(lock, orig_sha1, logmsg, 0, &err)) {
-		error("unable to write current sha1 into %s: %s", newrefname, err.buf);
-		strbuf_release(&err);
-		goto rollback;
-	}
-
-	return 0;
-
- rollback:
-	lock = lock_ref_sha1_basic(oldrefname, NULL, NULL, NULL, 0, NULL, &err);
-	if (!lock) {
-		error("unable to lock %s for rollback: %s", oldrefname, err.buf);
-		strbuf_release(&err);
-		goto rollbacklog;
-	}
-
-	flag = log_all_ref_updates;
-	log_all_ref_updates = 0;
-	if (write_ref_to_lockfile(lock, orig_sha1, &err) ||
-	    commit_ref_update(lock, orig_sha1, NULL, 0, &err)) {
-		error("unable to write current sha1 into %s: %s", oldrefname, err.buf);
-		strbuf_release(&err);
-	}
-	log_all_ref_updates = flag;
-
- rollbacklog:
-	if (logmoved && rename(git_path("logs/%s", newrefname), git_path("logs/%s", oldrefname)))
-		error("unable to restore logfile %s from %s: %s",
-			oldrefname, newrefname, strerror(errno));
-	if (!logmoved && log &&
-	    rename(git_path(TMP_RENAMED_LOG), git_path("logs/%s", oldrefname)))
-		error("unable to restore logfile %s from "TMP_RENAMED_LOG": %s",
-			oldrefname, strerror(errno));
-
-	return 1;
-}
-
-static int close_ref(struct ref_lock *lock)
-{
-	if (close_lock_file(lock->lk))
-		return -1;
-	return 0;
-}
-
-static int commit_ref(struct ref_lock *lock)
-{
-	if (commit_lock_file(lock->lk))
-		return -1;
-	return 0;
-}
-
-/*
- * copy the reflog message msg to buf, which has been allocated sufficiently
- * large, while cleaning up the whitespaces.  Especially, convert LF to space,
- * because reflog file is one line per entry.
- */
-static int copy_msg(char *buf, const char *msg)
-{
-	char *cp = buf;
-	char c;
-	int wasspace = 1;
-
-	*cp++ = '\t';
-	while ((c = *msg++)) {
-		if (wasspace && isspace(c))
-			continue;
-		wasspace = isspace(c);
-		if (wasspace)
-			c = ' ';
-		*cp++ = c;
-	}
-	while (buf < cp && isspace(cp[-1]))
-		cp--;
-	*cp++ = '\n';
-	return cp - buf;
-}
-
-static int should_autocreate_reflog(const char *refname)
-{
-	if (!log_all_ref_updates)
-		return 0;
-	return starts_with(refname, "refs/heads/") ||
-		starts_with(refname, "refs/remotes/") ||
-		starts_with(refname, "refs/notes/") ||
-		!strcmp(refname, "HEAD");
-}
-
-/*
- * Create a reflog for a ref.  If force_create = 0, the reflog will
- * only be created for certain refs (those for which
- * should_autocreate_reflog returns non-zero.  Otherwise, create it
- * regardless of the ref name.  Fill in *err and return -1 on failure.
- */
-static int log_ref_setup(const char *refname, struct strbuf *logfile, struct strbuf *err, int force_create)
-{
-	int logfd, oflags = O_APPEND | O_WRONLY;
-
-	strbuf_git_path(logfile, "logs/%s", refname);
-	if (force_create || should_autocreate_reflog(refname)) {
-		if (safe_create_leading_directories(logfile->buf) < 0) {
-			strbuf_addf(err, "unable to create directory for %s: "
-				    "%s", logfile->buf, strerror(errno));
-			return -1;
-		}
-		oflags |= O_CREAT;
-	}
-
-	logfd = open(logfile->buf, oflags, 0666);
-	if (logfd < 0) {
-		if (!(oflags & O_CREAT) && (errno == ENOENT || errno == EISDIR))
-			return 0;
-
-		if (errno == EISDIR) {
-			if (remove_empty_directories(logfile)) {
-				strbuf_addf(err, "There are still logs under "
-					    "'%s'", logfile->buf);
-				return -1;
-			}
-			logfd = open(logfile->buf, oflags, 0666);
-		}
-
-		if (logfd < 0) {
-			strbuf_addf(err, "unable to append to %s: %s",
-				    logfile->buf, strerror(errno));
-			return -1;
-		}
-	}
-
-	adjust_shared_perm(logfile->buf);
-	close(logfd);
-	return 0;
-}
-
-
-int safe_create_reflog(const char *refname, int force_create, struct strbuf *err)
-{
-	int ret;
-	struct strbuf sb = STRBUF_INIT;
-
-	ret = log_ref_setup(refname, &sb, err, force_create);
-	strbuf_release(&sb);
-	return ret;
-}
-
-static int log_ref_write_fd(int fd, const unsigned char *old_sha1,
-			    const unsigned char *new_sha1,
-			    const char *committer, const char *msg)
-{
-	int msglen, written;
-	unsigned maxlen, len;
-	char *logrec;
-
-	msglen = msg ? strlen(msg) : 0;
-	maxlen = strlen(committer) + msglen + 100;
-	logrec = xmalloc(maxlen);
-	len = sprintf(logrec, "%s %s %s\n",
-		      sha1_to_hex(old_sha1),
-		      sha1_to_hex(new_sha1),
-		      committer);
-	if (msglen)
-		len += copy_msg(logrec + len - 1, msg) - 1;
-
-	written = len <= maxlen ? write_in_full(fd, logrec, len) : -1;
-	free(logrec);
-	if (written != len)
-		return -1;
-
-	return 0;
-}
-
-static int log_ref_write_1(const char *refname, const unsigned char *old_sha1,
-			   const unsigned char *new_sha1, const char *msg,
-			   struct strbuf *logfile, int flags,
-			   struct strbuf *err)
-{
-	int logfd, result, oflags = O_APPEND | O_WRONLY;
-
-	if (log_all_ref_updates < 0)
-		log_all_ref_updates = !is_bare_repository();
-
-	result = log_ref_setup(refname, logfile, err, flags & REF_FORCE_CREATE_REFLOG);
-
-	if (result)
-		return result;
-
-	logfd = open(logfile->buf, oflags);
-	if (logfd < 0)
-		return 0;
-	result = log_ref_write_fd(logfd, old_sha1, new_sha1,
-				  git_committer_info(0), msg);
-	if (result) {
-		strbuf_addf(err, "unable to append to %s: %s", logfile->buf,
-			    strerror(errno));
-		close(logfd);
-		return -1;
-	}
-	if (close(logfd)) {
-		strbuf_addf(err, "unable to append to %s: %s", logfile->buf,
-			    strerror(errno));
-		return -1;
-	}
-	return 0;
-}
-
-static int log_ref_write(const char *refname, const unsigned char *old_sha1,
-			 const unsigned char *new_sha1, const char *msg,
-			 int flags, struct strbuf *err)
-{
-	struct strbuf sb = STRBUF_INIT;
-	int ret = log_ref_write_1(refname, old_sha1, new_sha1, msg, &sb, flags,
-				  err);
-	strbuf_release(&sb);
-	return ret;
-}
-
-int is_branch(const char *refname)
-{
-	return !strcmp(refname, "HEAD") || starts_with(refname, "refs/heads/");
-}
-
-/*
- * Write sha1 into the open lockfile, then close the lockfile. On
- * errors, rollback the lockfile, fill in *err and
- * return -1.
- */
-static int write_ref_to_lockfile(struct ref_lock *lock,
-				 const unsigned char *sha1, struct strbuf *err)
-{
-	static char term = '\n';
-	struct object *o;
-	int fd;
-
-	o = parse_object(sha1);
-	if (!o) {
-		strbuf_addf(err,
-			    "Trying to write ref %s with nonexistent object %s",
-			    lock->ref_name, sha1_to_hex(sha1));
-		unlock_ref(lock);
-		return -1;
-	}
-	if (o->type != OBJ_COMMIT && is_branch(lock->ref_name)) {
-		strbuf_addf(err,
-			    "Trying to write non-commit object %s to branch %s",
-			    sha1_to_hex(sha1), lock->ref_name);
-		unlock_ref(lock);
-		return -1;
-	}
-	fd = get_lock_file_fd(lock->lk);
-	if (write_in_full(fd, sha1_to_hex(sha1), 40) != 40 ||
-	    write_in_full(fd, &term, 1) != 1 ||
-	    close_ref(lock) < 0) {
-		strbuf_addf(err,
-			    "Couldn't write %s", get_lock_file_path(lock->lk));
-		unlock_ref(lock);
-		return -1;
-	}
-	return 0;
-}
-
-/*
- * Commit a change to a loose reference that has already been written
- * to the loose reference lockfile. Also update the reflogs if
- * necessary, using the specified lockmsg (which can be NULL).
- */
-static int commit_ref_update(struct ref_lock *lock,
-			     const unsigned char *sha1, const char *logmsg,
-			     int flags, struct strbuf *err)
-{
-	clear_loose_ref_cache(&ref_cache);
-	if (log_ref_write(lock->ref_name, lock->old_oid.hash, sha1, logmsg, flags, err) < 0 ||
-	    (strcmp(lock->ref_name, lock->orig_ref_name) &&
-	     log_ref_write(lock->orig_ref_name, lock->old_oid.hash, sha1, logmsg, flags, err) < 0)) {
-		char *old_msg = strbuf_detach(err, NULL);
-		strbuf_addf(err, "Cannot update the ref '%s': %s",
-			    lock->ref_name, old_msg);
-		free(old_msg);
-		unlock_ref(lock);
-		return -1;
-	}
-	if (strcmp(lock->orig_ref_name, "HEAD") != 0) {
-		/*
-		 * Special hack: If a branch is updated directly and HEAD
-		 * points to it (may happen on the remote side of a push
-		 * for example) then logically the HEAD reflog should be
-		 * updated too.
-		 * A generic solution implies reverse symref information,
-		 * but finding all symrefs pointing to the given branch
-		 * would be rather costly for this rare event (the direct
-		 * update of a branch) to be worth it.  So let's cheat and
-		 * check with HEAD only which should cover 99% of all usage
-		 * scenarios (even 100% of the default ones).
-		 */
-		unsigned char head_sha1[20];
-		int head_flag;
-		const char *head_ref;
-		head_ref = resolve_ref_unsafe("HEAD", RESOLVE_REF_READING,
-					      head_sha1, &head_flag);
-		if (head_ref && (head_flag & REF_ISSYMREF) &&
-		    !strcmp(head_ref, lock->ref_name)) {
-			struct strbuf log_err = STRBUF_INIT;
-			if (log_ref_write("HEAD", lock->old_oid.hash, sha1,
-					  logmsg, 0, &log_err)) {
-				error("%s", log_err.buf);
-				strbuf_release(&log_err);
-			}
-		}
-	}
-	if (commit_ref(lock)) {
-		error("Couldn't set %s", lock->ref_name);
-		unlock_ref(lock);
-		return -1;
+
+		unlink(filename);
+		rollback_lock_file(&lock);
+	} else {
+		unlink(filename);
 	}
 
-	unlock_ref(lock);
 	return 0;
 }
 
-int create_symref(const char *ref_target, const char *refs_heads_master,
-		  const char *logmsg)
+int delete_ref(const char *refname, const unsigned char *old_sha1,
+	       unsigned int flags)
 {
-	char *lockpath = NULL;
-	char ref[1000];
-	int fd, len, written;
-	char *git_HEAD = git_pathdup("%s", ref_target);
-	unsigned char old_sha1[20], new_sha1[20];
+	struct ref_transaction *transaction;
 	struct strbuf err = STRBUF_INIT;
 
-	if (logmsg && read_ref(ref_target, old_sha1))
-		hashclr(old_sha1);
-
-	if (safe_create_leading_directories(git_HEAD) < 0)
-		return error("unable to create directory for %s", git_HEAD);
+	if (ref_type(refname) == REF_TYPE_PSEUDOREF)
+		return delete_pseudoref(refname, old_sha1);
 
-#ifndef NO_SYMLINK_HEAD
-	if (prefer_symlink_refs) {
-		unlink(git_HEAD);
-		if (!symlink(refs_heads_master, git_HEAD))
-			goto done;
-		fprintf(stderr, "no symlink - falling back to symbolic ref\n");
+	transaction = ref_transaction_begin(&err);
+	if (!transaction ||
+	    ref_transaction_delete(transaction, refname, old_sha1,
+				   flags, NULL, &err) ||
+	    ref_transaction_commit(transaction, &err)) {
+		error("%s", err.buf);
+		ref_transaction_free(transaction);
+		strbuf_release(&err);
+		return 1;
 	}
-#endif
+	ref_transaction_free(transaction);
+	strbuf_release(&err);
+	return 0;
+}
 
-	len = snprintf(ref, sizeof(ref), "ref: %s\n", refs_heads_master);
-	if (sizeof(ref) <= len) {
-		error("refname too long: %s", refs_heads_master);
-		goto error_free_return;
-	}
-	lockpath = mkpathdup("%s.lock", git_HEAD);
-	fd = open(lockpath, O_CREAT | O_EXCL | O_WRONLY, 0666);
-	if (fd < 0) {
-		error("Unable to open %s for writing", lockpath);
-		goto error_free_return;
-	}
-	written = write_in_full(fd, ref, len);
-	if (close(fd) != 0 || written != len) {
-		error("Unable to write to %s", lockpath);
-		goto error_unlink_return;
-	}
-	if (rename(lockpath, git_HEAD) < 0) {
-		error("Unable to create %s", git_HEAD);
-		goto error_unlink_return;
-	}
-	if (adjust_shared_perm(git_HEAD)) {
-		error("Unable to fix permissions on %s", lockpath);
-	error_unlink_return:
-		unlink_or_warn(lockpath);
-	error_free_return:
-		free(lockpath);
-		free(git_HEAD);
-		return -1;
-	}
-	free(lockpath);
+int copy_reflog_msg(char *buf, const char *msg)
+{
+	char *cp = buf;
+	char c;
+	int wasspace = 1;
 
-#ifndef NO_SYMLINK_HEAD
-	done:
-#endif
-	if (logmsg && !read_ref(refs_heads_master, new_sha1) &&
-		log_ref_write(ref_target, old_sha1, new_sha1, logmsg, 0, &err)) {
-		error("%s", err.buf);
-		strbuf_release(&err);
+	*cp++ = '\t';
+	while ((c = *msg++)) {
+		if (wasspace && isspace(c))
+			continue;
+		wasspace = isspace(c);
+		if (wasspace)
+			c = ' ';
+		*cp++ = c;
 	}
+	while (buf < cp && isspace(cp[-1]))
+		cp--;
+	*cp++ = '\n';
+	return cp - buf;
+}
 
-	free(git_HEAD);
-	return 0;
+int should_autocreate_reflog(const char *refname)
+{
+	if (!log_all_ref_updates)
+		return 0;
+	return starts_with(refname, "refs/heads/") ||
+		starts_with(refname, "refs/remotes/") ||
+		starts_with(refname, "refs/notes/") ||
+		!strcmp(refname, "HEAD");
+}
+
+int is_branch(const char *refname)
+{
+	return !strcmp(refname, "HEAD") || starts_with(refname, "refs/heads/");
 }
 
 struct read_ref_at_cb {
 	const char *refname;
 	unsigned long at_time;
 	int cnt;
