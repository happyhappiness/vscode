 }
 
 int ref_transaction_update(struct ref_transaction *transaction,
 			   const char *refname,
 			   const unsigned char *new_sha1,
 			   const unsigned char *old_sha1,
-			   int flags, int have_old,
+			   int flags, int have_old, const char *msg,
 			   struct strbuf *err)
 {
 	struct ref_update *update;
 
+	assert(err);
+
+	if (transaction->state != REF_TRANSACTION_OPEN)
+		die("BUG: update called for transaction that is not open");
+
 	if (have_old && !old_sha1)
 		die("BUG: have_old is true but old_sha1 is NULL");
 
+	if (!is_null_sha1(new_sha1) &&
+	    check_refname_format(refname, REFNAME_ALLOW_ONELEVEL)) {
+		strbuf_addf(err, "refusing to update ref with bad name %s",
+			    refname);
+		return -1;
+	}
+
 	update = add_update(transaction, refname);
 	hashcpy(update->new_sha1, new_sha1);
 	update->flags = flags;
 	update->have_old = have_old;
 	if (have_old)
 		hashcpy(update->old_sha1, old_sha1);
+	if (msg)
+		update->msg = xstrdup(msg);
 	return 0;
 }
 
-void ref_transaction_create(struct ref_transaction *transaction,
-			    const char *refname,
-			    const unsigned char *new_sha1,
-			    int flags)
+int ref_transaction_create(struct ref_transaction *transaction,
+			   const char *refname,
+			   const unsigned char *new_sha1,
+			   int flags, const char *msg,
+			   struct strbuf *err)
 {
-	struct ref_update *update = add_update(transaction, refname);
+	struct ref_update *update;
+
+	assert(err);
+
+	if (transaction->state != REF_TRANSACTION_OPEN)
+		die("BUG: create called for transaction that is not open");
+
+	if (!new_sha1 || is_null_sha1(new_sha1))
+		die("BUG: create ref with null new_sha1");
+
+	if (check_refname_format(refname, REFNAME_ALLOW_ONELEVEL)) {
+		strbuf_addf(err, "refusing to create ref with bad name %s",
+			    refname);
+		return -1;
+	}
+
+	update = add_update(transaction, refname);
 
-	assert(!is_null_sha1(new_sha1));
 	hashcpy(update->new_sha1, new_sha1);
 	hashclr(update->old_sha1);
 	update->flags = flags;
 	update->have_old = 1;
+	if (msg)
+		update->msg = xstrdup(msg);
+	return 0;
 }
 
-void ref_transaction_delete(struct ref_transaction *transaction,
-			    const char *refname,
-			    const unsigned char *old_sha1,
-			    int flags, int have_old)
+int ref_transaction_delete(struct ref_transaction *transaction,
+			   const char *refname,
+			   const unsigned char *old_sha1,
+			   int flags, int have_old, const char *msg,
+			   struct strbuf *err)
 {
-	struct ref_update *update = add_update(transaction, refname);
+	struct ref_update *update;
+
+	assert(err);
 
+	if (transaction->state != REF_TRANSACTION_OPEN)
+		die("BUG: delete called for transaction that is not open");
+
+	if (have_old && !old_sha1)
+		die("BUG: have_old is true but old_sha1 is NULL");
+
+	update = add_update(transaction, refname);
 	update->flags = flags;
 	update->have_old = have_old;
 	if (have_old) {
 		assert(!is_null_sha1(old_sha1));
 		hashcpy(update->old_sha1, old_sha1);
 	}
+	if (msg)
+		update->msg = xstrdup(msg);
+	return 0;
 }
 
 int update_ref(const char *action, const char *refname,
 	       const unsigned char *sha1, const unsigned char *oldval,
 	       int flags, enum action_on_err onerr)
 {
-	struct ref_lock *lock;
-	lock = update_ref_lock(refname, oldval, flags, NULL, onerr);
-	if (!lock)
+	struct ref_transaction *t;
+	struct strbuf err = STRBUF_INIT;
+
+	t = ref_transaction_begin(&err);
+	if (!t ||
+	    ref_transaction_update(t, refname, sha1, oldval, flags,
+				   !!oldval, action, &err) ||
+	    ref_transaction_commit(t, &err)) {
+		const char *str = "update_ref failed for ref '%s': %s";
+
+		ref_transaction_free(t);
+		switch (onerr) {
+		case UPDATE_REFS_MSG_ON_ERR:
+			error(str, refname, err.buf);
+			break;
+		case UPDATE_REFS_DIE_ON_ERR:
+			die(str, refname, err.buf);
+			break;
+		case UPDATE_REFS_QUIET_ON_ERR:
+			break;
+		}
+		strbuf_release(&err);
 		return 1;
-	return update_ref_write(action, refname, sha1, lock, NULL, onerr);
+	}
+	strbuf_release(&err);
+	ref_transaction_free(t);
+	return 0;
 }
 
 static int ref_update_compare(const void *r1, const void *r2)
 {
 	const struct ref_update * const *u1 = r1;
 	const struct ref_update * const *u2 = r2;
