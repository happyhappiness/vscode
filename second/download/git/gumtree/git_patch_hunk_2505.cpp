 }
 
 static void write_remote_refs(const struct ref *local_refs)
 {
 	const struct ref *r;
 
-	lock_packed_refs(LOCK_DIE_ON_ERROR);
+	struct ref_transaction *t;
+	struct strbuf err = STRBUF_INIT;
+
+	t = ref_transaction_begin(&err);
+	if (!t)
+		die("%s", err.buf);
 
 	for (r = local_refs; r; r = r->next) {
 		if (!r->peer_ref)
 			continue;
-		add_packed_ref(r->peer_ref->name, r->old_sha1);
+		if (ref_transaction_create(t, r->peer_ref->name, r->old_sha1,
+					   0, NULL, &err))
+			die("%s", err.buf);
 	}
 
-	if (commit_packed_refs())
-		die_errno("unable to overwrite old ref-pack file");
+	if (initial_ref_transaction_commit(t, &err))
+		die("%s", err.buf);
+
+	strbuf_release(&err);
+	ref_transaction_free(t);
 }
 
 static void write_followtags(const struct ref *refs, const char *msg)
 {
 	const struct ref *ref;
 	for (ref = refs; ref; ref = ref->next) {
