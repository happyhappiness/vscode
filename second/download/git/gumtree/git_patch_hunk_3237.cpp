 	}
 
 	unlock_ref(lock);
 	return 0;
 }
 
-int create_symref(const char *ref_target, const char *refs_heads_master,
-		  const char *logmsg)
+static int create_ref_symlink(struct ref_lock *lock, const char *target)
 {
-	char *lockpath = NULL;
-	char ref[1000];
-	int fd, len, written;
-	char *git_HEAD = git_pathdup("%s", ref_target);
-	unsigned char old_sha1[20], new_sha1[20];
-	struct strbuf err = STRBUF_INIT;
-
-	if (logmsg && read_ref(ref_target, old_sha1))
-		hashclr(old_sha1);
-
-	if (safe_create_leading_directories(git_HEAD) < 0)
-		return error("unable to create directory for %s", git_HEAD);
-
+	int ret = -1;
 #ifndef NO_SYMLINK_HEAD
-	if (prefer_symlink_refs) {
-		unlink(git_HEAD);
-		if (!symlink(refs_heads_master, git_HEAD))
-			goto done;
+	char *ref_path = get_locked_file_path(lock->lk);
+	unlink(ref_path);
+	ret = symlink(target, ref_path);
+	free(ref_path);
+
+	if (ret)
 		fprintf(stderr, "no symlink - falling back to symbolic ref\n");
-	}
 #endif
+	return ret;
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
+static void update_symref_reflog(struct ref_lock *lock, const char *refname,
+				 const char *target, const char *logmsg)
+{
+	struct strbuf err = STRBUF_INIT;
+	unsigned char new_sha1[20];
+	if (logmsg && !read_ref(target, new_sha1) &&
+	    log_ref_write(refname, lock->old_oid.hash, new_sha1, logmsg, 0, &err)) {
+		error("%s", err.buf);
+		strbuf_release(&err);
 	}
-	free(lockpath);
+}
 
-#ifndef NO_SYMLINK_HEAD
-	done:
-#endif
-	if (logmsg && !read_ref(refs_heads_master, new_sha1) &&
-		log_ref_write(ref_target, old_sha1, new_sha1, logmsg, 0, &err)) {
+static int create_symref_locked(struct ref_lock *lock, const char *refname,
+				const char *target, const char *logmsg)
+{
+	if (prefer_symlink_refs && !create_ref_symlink(lock, target)) {
+		update_symref_reflog(lock, refname, target, logmsg);
+		return 0;
+	}
+
+	if (!fdopen_lock_file(lock->lk, "w"))
+		return error("unable to fdopen %s: %s",
+			     lock->lk->tempfile.filename.buf, strerror(errno));
+
+	update_symref_reflog(lock, refname, target, logmsg);
+
+	/* no error check; commit_ref will check ferror */
+	fprintf(lock->lk->tempfile.fp, "ref: %s\n", target);
+	if (commit_ref(lock) < 0)
+		return error("unable to write symref for %s: %s", refname,
+			     strerror(errno));
+	return 0;
+}
+
+int create_symref(const char *refname, const char *target, const char *logmsg)
+{
+	struct strbuf err = STRBUF_INIT;
+	struct ref_lock *lock;
+	int ret;
+
+	lock = lock_ref_sha1_basic(refname, NULL, NULL, NULL, REF_NODEREF, NULL,
+				   &err);
+	if (!lock) {
 		error("%s", err.buf);
 		strbuf_release(&err);
+		return -1;
 	}
 
-	free(git_HEAD);
-	return 0;
+	ret = create_symref_locked(lock, refname, target, logmsg);
+	unlock_ref(lock);
+	return ret;
 }
 
 int reflog_exists(const char *refname)
 {
 	struct stat st;
 
