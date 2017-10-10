 {
 	return ref_store_transaction_begin(get_main_ref_store(), err);
 }
 
 void ref_transaction_free(struct ref_transaction *transaction)
 {
-	int i;
+	size_t i;
 
 	if (!transaction)
 		return;
 
+	switch (transaction->state) {
+	case REF_TRANSACTION_OPEN:
+	case REF_TRANSACTION_CLOSED:
+		/* OK */
+		break;
+	case REF_TRANSACTION_PREPARED:
+		die("BUG: free called on a prepared reference transaction");
+		break;
+	default:
+		die("BUG: unexpected reference transaction state");
+		break;
+	}
+
 	for (i = 0; i < transaction->nr; i++) {
 		free(transaction->updates[i]->msg);
 		free(transaction->updates[i]);
 	}
 	free(transaction->updates);
 	free(transaction);
