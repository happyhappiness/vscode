 
 	return 0;
 }
 
 static int log_ref_write_1(const char *refname, const unsigned char *old_sha1,
 			   const unsigned char *new_sha1, const char *msg,
-			   struct strbuf *sb_log_file)
+			   struct strbuf *logfile, int flags,
+			   struct strbuf *err)
 {
 	int logfd, result, oflags = O_APPEND | O_WRONLY;
-	char *log_file;
 
 	if (log_all_ref_updates < 0)
 		log_all_ref_updates = !is_bare_repository();
 
-	result = log_ref_setup(refname, sb_log_file);
+	result = log_ref_setup(refname, logfile, err, flags & REF_FORCE_CREATE_REFLOG);
+
 	if (result)
 		return result;
-	log_file = sb_log_file->buf;
-	/* make sure the rest of the function can't change "log_file" */
-	sb_log_file = NULL;
 
-	logfd = open(log_file, oflags);
+	logfd = open(logfile->buf, oflags);
 	if (logfd < 0)
 		return 0;
 	result = log_ref_write_fd(logfd, old_sha1, new_sha1,
 				  git_committer_info(0), msg);
 	if (result) {
-		int save_errno = errno;
+		strbuf_addf(err, "unable to append to %s: %s", logfile->buf,
+			    strerror(errno));
 		close(logfd);
-		error("Unable to append to %s", log_file);
-		errno = save_errno;
 		return -1;
 	}
 	if (close(logfd)) {
-		int save_errno = errno;
-		error("Unable to append to %s", log_file);
-		errno = save_errno;
+		strbuf_addf(err, "unable to append to %s: %s", logfile->buf,
+			    strerror(errno));
 		return -1;
 	}
 	return 0;
 }
 
 static int log_ref_write(const char *refname, const unsigned char *old_sha1,
-			 const unsigned char *new_sha1, const char *msg)
+			 const unsigned char *new_sha1, const char *msg,
+			 int flags, struct strbuf *err)
 {
 	struct strbuf sb = STRBUF_INIT;
-	int ret = log_ref_write_1(refname, old_sha1, new_sha1, msg, &sb);
+	int ret = log_ref_write_1(refname, old_sha1, new_sha1, msg, &sb, flags,
+				  err);
 	strbuf_release(&sb);
 	return ret;
 }
 
 int is_branch(const char *refname)
 {
 	return !strcmp(refname, "HEAD") || starts_with(refname, "refs/heads/");
 }
 
 /*
  * Write sha1 into the open lockfile, then close the lockfile. On
- * errors, rollback the lockfile and set errno to reflect the problem.
+ * errors, rollback the lockfile, fill in *err and
+ * return -1.
  */
 static int write_ref_to_lockfile(struct ref_lock *lock,
-				 const unsigned char *sha1)
+				 const unsigned char *sha1, struct strbuf *err)
 {
 	static char term = '\n';
 	struct object *o;
+	int fd;
 
 	o = parse_object(sha1);
 	if (!o) {
-		error("Trying to write ref %s with nonexistent object %s",
-			lock->ref_name, sha1_to_hex(sha1));
+		strbuf_addf(err,
+			    "Trying to write ref %s with nonexistent object %s",
+			    lock->ref_name, sha1_to_hex(sha1));
 		unlock_ref(lock);
-		errno = EINVAL;
 		return -1;
 	}
 	if (o->type != OBJ_COMMIT && is_branch(lock->ref_name)) {
-		error("Trying to write non-commit object %s to branch %s",
-			sha1_to_hex(sha1), lock->ref_name);
+		strbuf_addf(err,
+			    "Trying to write non-commit object %s to branch %s",
+			    sha1_to_hex(sha1), lock->ref_name);
 		unlock_ref(lock);
-		errno = EINVAL;
 		return -1;
 	}
-	if (write_in_full(lock->lk->fd, sha1_to_hex(sha1), 40) != 40 ||
-	    write_in_full(lock->lk->fd, &term, 1) != 1 ||
+	fd = get_lock_file_fd(lock->lk);
+	if (write_in_full(fd, sha1_to_hex(sha1), 40) != 40 ||
+	    write_in_full(fd, &term, 1) != 1 ||
 	    close_ref(lock) < 0) {
-		int save_errno = errno;
-		error("Couldn't write %s", lock->lk->filename.buf);
+		strbuf_addf(err,
+			    "Couldn't write %s", get_lock_file_path(lock->lk));
 		unlock_ref(lock);
-		errno = save_errno;
 		return -1;
 	}
 	return 0;
 }
 
 /*
  * Commit a change to a loose reference that has already been written
  * to the loose reference lockfile. Also update the reflogs if
  * necessary, using the specified lockmsg (which can be NULL).
  */
 static int commit_ref_update(struct ref_lock *lock,
-			     const unsigned char *sha1, const char *logmsg)
+			     const unsigned char *sha1, const char *logmsg,
+			     int flags, struct strbuf *err)
 {
 	clear_loose_ref_cache(&ref_cache);
-	if (log_ref_write(lock->ref_name, lock->old_oid.hash, sha1, logmsg) < 0 ||
+	if (log_ref_write(lock->ref_name, lock->old_oid.hash, sha1, logmsg, flags, err) < 0 ||
 	    (strcmp(lock->ref_name, lock->orig_ref_name) &&
-	     log_ref_write(lock->orig_ref_name, lock->old_oid.hash, sha1, logmsg) < 0)) {
+	     log_ref_write(lock->orig_ref_name, lock->old_oid.hash, sha1, logmsg, flags, err) < 0)) {
+		char *old_msg = strbuf_detach(err, NULL);
+		strbuf_addf(err, "Cannot update the ref '%s': %s",
+			    lock->ref_name, old_msg);
+		free(old_msg);
 		unlock_ref(lock);
 		return -1;
 	}
 	if (strcmp(lock->orig_ref_name, "HEAD") != 0) {
 		/*
 		 * Special hack: If a branch is updated directly and HEAD
