 }
 
 static int write_ref_to_lockfile(struct ref_lock *lock,
 				 const unsigned char *sha1, struct strbuf *err);
 static int commit_ref_update(struct ref_lock *lock,
 			     const unsigned char *sha1, const char *logmsg,
-			     int flags, struct strbuf *err);
+			     struct strbuf *err);
 
 int rename_ref(const char *oldrefname, const char *newrefname, const char *logmsg)
 {
 	unsigned char sha1[20], orig_sha1[20];
 	int flag = 0, logmoved = 0;
 	struct ref_lock *lock;
 	struct stat loginfo;
 	int log = !lstat(git_path("logs/%s", oldrefname), &loginfo);
-	const char *symref = NULL;
 	struct strbuf err = STRBUF_INIT;
 
 	if (log && S_ISLNK(loginfo.st_mode))
 		return error("reflog for %s is a symlink", oldrefname);
 
-	symref = resolve_ref_unsafe(oldrefname, RESOLVE_REF_READING,
-				    orig_sha1, &flag);
+	if (!resolve_ref_unsafe(oldrefname, RESOLVE_REF_READING | RESOLVE_REF_NO_RECURSE,
+				orig_sha1, &flag))
+		return error("refname %s not found", oldrefname);
+
 	if (flag & REF_ISSYMREF)
 		return error("refname %s is a symbolic ref, renaming it is not supported",
 			oldrefname);
-	if (!symref)
-		return error("refname %s not found", oldrefname);
-
 	if (!rename_ref_available(oldrefname, newrefname))
 		return 1;
 
 	if (log && rename(git_path("logs/%s", oldrefname), git_path(TMP_RENAMED_LOG)))
 		return error("unable to move logfile logs/%s to "TMP_RENAMED_LOG": %s",
 			oldrefname, strerror(errno));
 
 	if (delete_ref(oldrefname, orig_sha1, REF_NODEREF)) {
 		error("unable to delete old %s", oldrefname);
 		goto rollback;
 	}
 
-	if (!read_ref_full(newrefname, RESOLVE_REF_READING, sha1, NULL) &&
-	    delete_ref(newrefname, sha1, REF_NODEREF)) {
+	/*
+	 * Since we are doing a shallow lookup, sha1 is not the
+	 * correct value to pass to delete_ref as old_sha1. But that
+	 * doesn't matter, because an old_sha1 check wouldn't add to
+	 * the safety anyway; we want to delete the reference whatever
+	 * its current value.
+	 */
+	if (!read_ref_full(newrefname, RESOLVE_REF_READING | RESOLVE_REF_NO_RECURSE,
+			   sha1, NULL) &&
+	    delete_ref(newrefname, NULL, REF_NODEREF)) {
 		if (errno==EISDIR) {
 			struct strbuf path = STRBUF_INIT;
 			int result;
 
 			strbuf_git_path(&path, "%s", newrefname);
 			result = remove_empty_directories(&path);
