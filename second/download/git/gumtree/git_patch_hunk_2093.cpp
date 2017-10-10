 }
 
 int ref_transaction_update(struct ref_transaction *transaction,
 			   const char *refname,
 			   const unsigned char *new_sha1,
 			   const unsigned char *old_sha1,
-			   int flags, int have_old, const char *msg,
+			   unsigned int flags, const char *msg,
 			   struct strbuf *err)
 {
 	struct ref_update *update;
 
 	assert(err);
 
 	if (transaction->state != REF_TRANSACTION_OPEN)
 		die("BUG: update called for transaction that is not open");
 
-	if (have_old && !old_sha1)
-		die("BUG: have_old is true but old_sha1 is NULL");
-
-	if (!is_null_sha1(new_sha1) &&
+	if (new_sha1 && !is_null_sha1(new_sha1) &&
 	    check_refname_format(refname, REFNAME_ALLOW_ONELEVEL)) {
 		strbuf_addf(err, "refusing to update ref with bad name %s",
 			    refname);
 		return -1;
 	}
 
 	update = add_update(transaction, refname);
-	hashcpy(update->new_sha1, new_sha1);
-	update->flags = flags;
-	update->have_old = have_old;
-	if (have_old)
+	if (new_sha1) {
+		hashcpy(update->new_sha1, new_sha1);
+		flags |= REF_HAVE_NEW;
+	}
+	if (old_sha1) {
 		hashcpy(update->old_sha1, old_sha1);
+		flags |= REF_HAVE_OLD;
+	}
+	update->flags = flags;
 	if (msg)
 		update->msg = xstrdup(msg);
 	return 0;
 }
 
 int ref_transaction_create(struct ref_transaction *transaction,
 			   const char *refname,
 			   const unsigned char *new_sha1,
-			   int flags, const char *msg,
+			   unsigned int flags, const char *msg,
 			   struct strbuf *err)
 {
-	struct ref_update *update;
-
-	assert(err);
-
-	if (transaction->state != REF_TRANSACTION_OPEN)
-		die("BUG: create called for transaction that is not open");
-
 	if (!new_sha1 || is_null_sha1(new_sha1))
-		die("BUG: create ref with null new_sha1");
-
-	if (check_refname_format(refname, REFNAME_ALLOW_ONELEVEL)) {
-		strbuf_addf(err, "refusing to create ref with bad name %s",
-			    refname);
-		return -1;
-	}
-
-	update = add_update(transaction, refname);
-
-	hashcpy(update->new_sha1, new_sha1);
-	hashclr(update->old_sha1);
-	update->flags = flags;
-	update->have_old = 1;
-	if (msg)
-		update->msg = xstrdup(msg);
-	return 0;
+		die("BUG: create called without valid new_sha1");
+	return ref_transaction_update(transaction, refname, new_sha1,
+				      null_sha1, flags, msg, err);
 }
 
 int ref_transaction_delete(struct ref_transaction *transaction,
 			   const char *refname,
 			   const unsigned char *old_sha1,
-			   int flags, int have_old, const char *msg,
+			   unsigned int flags, const char *msg,
 			   struct strbuf *err)
 {
-	struct ref_update *update;
-
-	assert(err);
-
-	if (transaction->state != REF_TRANSACTION_OPEN)
-		die("BUG: delete called for transaction that is not open");
-
-	if (have_old && !old_sha1)
-		die("BUG: have_old is true but old_sha1 is NULL");
+	if (old_sha1 && is_null_sha1(old_sha1))
+		die("BUG: delete called with old_sha1 set to zeros");
+	return ref_transaction_update(transaction, refname,
+				      null_sha1, old_sha1,
+				      flags, msg, err);
+}
 
-	update = add_update(transaction, refname);
-	update->flags = flags;
-	update->have_old = have_old;
-	if (have_old) {
-		assert(!is_null_sha1(old_sha1));
-		hashcpy(update->old_sha1, old_sha1);
-	}
-	if (msg)
-		update->msg = xstrdup(msg);
-	return 0;
+int ref_transaction_verify(struct ref_transaction *transaction,
+			   const char *refname,
+			   const unsigned char *old_sha1,
+			   unsigned int flags,
+			   struct strbuf *err)
+{
+	if (!old_sha1)
+		die("BUG: verify called with old_sha1 set to NULL");
+	return ref_transaction_update(transaction, refname,
+				      NULL, old_sha1,
+				      flags, NULL, err);
 }
 
-int update_ref(const char *action, const char *refname,
-	       const unsigned char *sha1, const unsigned char *oldval,
-	       int flags, enum action_on_err onerr)
+int update_ref(const char *msg, const char *refname,
+	       const unsigned char *new_sha1, const unsigned char *old_sha1,
+	       unsigned int flags, enum action_on_err onerr)
 {
 	struct ref_transaction *t;
 	struct strbuf err = STRBUF_INIT;
 
 	t = ref_transaction_begin(&err);
 	if (!t ||
-	    ref_transaction_update(t, refname, sha1, oldval, flags,
-				   !!oldval, action, &err) ||
+	    ref_transaction_update(t, refname, new_sha1, old_sha1,
+				   flags, msg, &err) ||
 	    ref_transaction_commit(t, &err)) {
 		const char *str = "update_ref failed for ref '%s': %s";
 
 		ref_transaction_free(t);
 		switch (onerr) {
 		case UPDATE_REFS_MSG_ON_ERR:
