 	if (ret)
 		fprintf(stderr, "no symlink - falling back to symbolic ref\n");
 #endif
 	return ret;
 }
 
-static void update_symref_reflog(struct ref_lock *lock, const char *refname,
+static void update_symref_reflog(struct files_ref_store *refs,
+				 struct ref_lock *lock, const char *refname,
 				 const char *target, const char *logmsg)
 {
 	struct strbuf err = STRBUF_INIT;
 	unsigned char new_sha1[20];
-	if (logmsg && !read_ref(target, new_sha1) &&
-	    log_ref_write(refname, lock->old_oid.hash, new_sha1, logmsg, 0, &err)) {
+	if (logmsg &&
+	    !refs_read_ref_full(&refs->base, target,
+				RESOLVE_REF_READING, new_sha1, NULL) &&
+	    files_log_ref_write(refs, refname, lock->old_oid.hash,
+				new_sha1, logmsg, 0, &err)) {
 		error("%s", err.buf);
 		strbuf_release(&err);
 	}
 }
 
-static int create_symref_locked(struct ref_lock *lock, const char *refname,
+static int create_symref_locked(struct files_ref_store *refs,
+				struct ref_lock *lock, const char *refname,
 				const char *target, const char *logmsg)
 {
 	if (prefer_symlink_refs && !create_ref_symlink(lock, target)) {
-		update_symref_reflog(lock, refname, target, logmsg);
+		update_symref_reflog(refs, lock, refname, target, logmsg);
 		return 0;
 	}
 
 	if (!fdopen_lock_file(lock->lk, "w"))
 		return error("unable to fdopen %s: %s",
 			     lock->lk->tempfile.filename.buf, strerror(errno));
 
-	update_symref_reflog(lock, refname, target, logmsg);
+	update_symref_reflog(refs, lock, refname, target, logmsg);
 
 	/* no error check; commit_ref will check ferror */
 	fprintf(lock->lk->tempfile.fp, "ref: %s\n", target);
 	if (commit_ref(lock) < 0)
 		return error("unable to write symref for %s: %s", refname,
 			     strerror(errno));
