 }
 
 int update_ref(const char *msg, const char *refname,
 	       const unsigned char *new_sha1, const unsigned char *old_sha1,
 	       unsigned int flags, enum action_on_err onerr)
 {
-	struct ref_transaction *t;
+	struct ref_transaction *t = NULL;
 	struct strbuf err = STRBUF_INIT;
+	int ret = 0;
 
-	t = ref_transaction_begin(&err);
-	if (!t ||
-	    ref_transaction_update(t, refname, new_sha1, old_sha1,
-				   flags, msg, &err) ||
-	    ref_transaction_commit(t, &err)) {
+	if (ref_type(refname) == REF_TYPE_PSEUDOREF) {
+		ret = write_pseudoref(refname, new_sha1, old_sha1, &err);
+	} else {
+		t = ref_transaction_begin(&err);
+		if (!t ||
+		    ref_transaction_update(t, refname, new_sha1, old_sha1,
+					   flags, msg, &err) ||
+		    ref_transaction_commit(t, &err)) {
+			ret = 1;
+			ref_transaction_free(t);
+		}
+	}
+	if (ret) {
 		const char *str = "update_ref failed for ref '%s': %s";
 
-		ref_transaction_free(t);
 		switch (onerr) {
 		case UPDATE_REFS_MSG_ON_ERR:
 			error(str, refname, err.buf);
 			break;
 		case UPDATE_REFS_DIE_ON_ERR:
 			die(str, refname, err.buf);
