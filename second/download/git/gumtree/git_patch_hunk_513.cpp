 	if (commit_ref(lock) < 0)
 		return error("unable to write symref for %s: %s", refname,
 			     strerror(errno));
 	return 0;
 }
 
-int create_symref(const char *refname, const char *target, const char *logmsg)
+static int files_create_symref(struct ref_store *ref_store,
+			       const char *refname, const char *target,
+			       const char *logmsg)
 {
+	struct files_ref_store *refs =
+		files_downcast(ref_store, 0, "create_symref");
 	struct strbuf err = STRBUF_INIT;
 	struct ref_lock *lock;
 	int ret;
 
-	lock = lock_ref_sha1_basic(refname, NULL, NULL, NULL, REF_NODEREF, NULL,
+	lock = lock_ref_sha1_basic(refs, refname, NULL,
+				   NULL, NULL, REF_NODEREF, NULL,
 				   &err);
 	if (!lock) {
 		error("%s", err.buf);
 		strbuf_release(&err);
 		return -1;
 	}
