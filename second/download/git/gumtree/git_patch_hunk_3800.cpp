 }
 
 int initial_ref_transaction_commit(struct ref_transaction *transaction,
 				   struct strbuf *err)
 {
 	int ret = 0, i;
-	int n = transaction->nr;
-	struct ref_update **updates = transaction->updates;
 	struct string_list affected_refnames = STRING_LIST_INIT_NODUP;
 
 	assert(err);
 
 	if (transaction->state != REF_TRANSACTION_OPEN)
 		die("BUG: commit called for transaction that is not open");
 
 	/* Fail if a refname appears more than once in the transaction: */
-	for (i = 0; i < n; i++)
-		string_list_append(&affected_refnames, updates[i]->refname);
+	for (i = 0; i < transaction->nr; i++)
+		string_list_append(&affected_refnames,
+				   transaction->updates[i]->refname);
 	string_list_sort(&affected_refnames);
 	if (ref_update_reject_duplicates(&affected_refnames, err)) {
 		ret = TRANSACTION_GENERIC_ERROR;
 		goto cleanup;
 	}
 
