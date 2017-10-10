 	return 0;
 }
 
 static int rename_ref_available(const char *oldname, const char *newname)
 {
 	struct string_list skip = STRING_LIST_INIT_NODUP;
+	struct strbuf err = STRBUF_INIT;
 	int ret;
 
 	string_list_insert(&skip, oldname);
-	ret = is_refname_available(newname, &skip, get_packed_refs(&ref_cache))
-	    && is_refname_available(newname, &skip, get_loose_refs(&ref_cache));
+	ret = !verify_refname_available(newname, NULL, &skip,
+					get_packed_refs(&ref_cache), &err)
+		&& !verify_refname_available(newname, NULL, &skip,
+					     get_loose_refs(&ref_cache), &err);
+	if (!ret)
+		error("%s", err.buf);
+
 	string_list_clear(&skip, 0);
+	strbuf_release(&err);
 	return ret;
 }
 
-static int write_ref_sha1(struct ref_lock *lock, const unsigned char *sha1,
-			  const char *logmsg);
+static int write_ref_to_lockfile(struct ref_lock *lock, const unsigned char *sha1);
+static int commit_ref_update(struct ref_lock *lock,
+			     const unsigned char *sha1, const char *logmsg);
 
 int rename_ref(const char *oldrefname, const char *newrefname, const char *logmsg)
 {
 	unsigned char sha1[20], orig_sha1[20];
 	int flag = 0, logmoved = 0;
 	struct ref_lock *lock;
 	struct stat loginfo;
 	int log = !lstat(git_path("logs/%s", oldrefname), &loginfo);
 	const char *symref = NULL;
+	struct strbuf err = STRBUF_INIT;
 
 	if (log && S_ISLNK(loginfo.st_mode))
 		return error("reflog for %s is a symlink", oldrefname);
 
 	symref = resolve_ref_unsafe(oldrefname, RESOLVE_REF_READING,
 				    orig_sha1, &flag);
