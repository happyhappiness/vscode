  * People using contrib's git-new-workdir have .git/logs/refs ->
  * /some/other/path/.git/logs/refs, and that may live on another device.
  *
  * IOW, to avoid cross device rename errors, the temporary renamed log must
  * live into logs/refs.
  */
-#define TMP_RENAMED_LOG  "logs/refs/.tmp-renamed-log"
+#define TMP_RENAMED_LOG  "refs/.tmp-renamed-log"
 
-static int rename_tmp_log(const char *newrefname)
-{
-	int attempts_remaining = 4;
-	struct strbuf path = STRBUF_INIT;
-	int ret = -1;
+struct rename_cb {
+	const char *tmp_renamed_log;
+	int true_errno;
+};
 
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
+static int rename_tmp_log_callback(const char *path, void *cb_data)
+{
+	struct rename_cb *cb = cb_data;
 
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
+	if (rename(cb->tmp_renamed_log, path)) {
+		/*
+		 * rename(a, b) when b is an existing directory ought
+		 * to result in ISDIR, but Solaris 5.8 gives ENOTDIR.
+		 * Sheesh. Record the true errno for error reporting,
+		 * but report EISDIR to raceproof_create_file() so
+		 * that it knows to retry.
+		 */
+		cb->true_errno = errno;
+		if (errno == ENOTDIR)
+			errno = EISDIR;
+		return -1;
+	} else {
+		return 0;
 	}
-	ret = 0;
-out:
-	strbuf_release(&path);
-	return ret;
 }
 
-static int files_verify_refname_available(struct ref_store *ref_store,
-					  const char *newname,
-					  const struct string_list *extras,
-					  const struct string_list *skip,
-					  struct strbuf *err)
+static int rename_tmp_log(struct files_ref_store *refs, const char *newrefname)
 {
-	struct files_ref_store *refs =
-		files_downcast(ref_store, 1, "verify_refname_available");
-	struct ref_dir *packed_refs = get_packed_refs(refs);
-	struct ref_dir *loose_refs = get_loose_refs(refs);
-
-	if (verify_refname_available_dir(newname, extras, skip,
-					 packed_refs, err) ||
-	    verify_refname_available_dir(newname, extras, skip,
-					 loose_refs, err))
-		return -1;
+	struct strbuf path = STRBUF_INIT;
+	struct strbuf tmp = STRBUF_INIT;
+	struct rename_cb cb;
+	int ret;
 
-	return 0;
+	files_reflog_path(refs, &path, newrefname);
+	files_reflog_path(refs, &tmp, TMP_RENAMED_LOG);
+	cb.tmp_renamed_log = tmp.buf;
+	ret = raceproof_create_file(path.buf, rename_tmp_log_callback, &cb);
+	if (ret) {
+		if (errno == EISDIR)
+			error("directory not empty: %s", path.buf);
+		else
+			error("unable to move logfile %s to %s: %s",
+			      tmp.buf, path.buf,
+			      strerror(cb.true_errno));
+	}
+
+	strbuf_release(&path);
+	strbuf_release(&tmp);
+	return ret;
 }
 
 static int write_ref_to_lockfile(struct ref_lock *lock,
 				 const unsigned char *sha1, struct strbuf *err);
 static int commit_ref_update(struct files_ref_store *refs,
 			     struct ref_lock *lock,
