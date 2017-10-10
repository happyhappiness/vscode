 		free(transaction->updates[i]);
 	}
 	free(transaction->updates);
 	free(transaction);
 }
 
-static struct ref_update *add_update(struct ref_transaction *transaction,
-				     const char *refname)
+struct ref_update *ref_transaction_add_update(
+		struct ref_transaction *transaction,
+		const char *refname, unsigned int flags,
+		const unsigned char *new_sha1,
+		const unsigned char *old_sha1,
+		const char *msg)
 {
 	struct ref_update *update;
+
+	if (transaction->state != REF_TRANSACTION_OPEN)
+		die("BUG: update called for transaction that is not open");
+
+	if ((flags & REF_ISPRUNING) && !(flags & REF_NODEREF))
+		die("BUG: REF_ISPRUNING set without REF_NODEREF");
+
 	FLEX_ALLOC_STR(update, refname, refname);
 	ALLOC_GROW(transaction->updates, transaction->nr + 1, transaction->alloc);
 	transaction->updates[transaction->nr++] = update;
+
+	update->flags = flags;
+
+	if (flags & REF_HAVE_NEW)
+		hashcpy(update->new_sha1, new_sha1);
+	if (flags & REF_HAVE_OLD)
+		hashcpy(update->old_sha1, old_sha1);
+	if (msg)
+		update->msg = xstrdup(msg);
 	return update;
 }
 
 int ref_transaction_update(struct ref_transaction *transaction,
 			   const char *refname,
 			   const unsigned char *new_sha1,
 			   const unsigned char *old_sha1,
 			   unsigned int flags, const char *msg,
 			   struct strbuf *err)
 {
-	struct ref_update *update;
-
 	assert(err);
 
-	if (transaction->state != REF_TRANSACTION_OPEN)
-		die("BUG: update called for transaction that is not open");
-
-	if (new_sha1 && !is_null_sha1(new_sha1) &&
-	    check_refname_format(refname, REFNAME_ALLOW_ONELEVEL)) {
-		strbuf_addf(err, "refusing to update ref with bad name %s",
+	if ((new_sha1 && !is_null_sha1(new_sha1)) ?
+	    check_refname_format(refname, REFNAME_ALLOW_ONELEVEL) :
+	    !refname_is_safe(refname)) {
+		strbuf_addf(err, "refusing to update ref with bad name '%s'",
 			    refname);
 		return -1;
 	}
 
-	update = add_update(transaction, refname);
-	if (new_sha1) {
-		hashcpy(update->new_sha1, new_sha1);
-		flags |= REF_HAVE_NEW;
-	}
-	if (old_sha1) {
-		hashcpy(update->old_sha1, old_sha1);
-		flags |= REF_HAVE_OLD;
-	}
-	update->flags = flags;
-	if (msg)
-		update->msg = xstrdup(msg);
+	flags |= (new_sha1 ? REF_HAVE_NEW : 0) | (old_sha1 ? REF_HAVE_OLD : 0);
+
+	ref_transaction_add_update(transaction, refname, flags,
+				   new_sha1, old_sha1, msg);
 	return 0;
 }
 
 int ref_transaction_create(struct ref_transaction *transaction,
 			   const char *refname,
 			   const unsigned char *new_sha1,
