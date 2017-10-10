 		if (res)
 			return 1;
 	}
 	return 0;
 }
 
-int delete_ref(const char *refname, const unsigned char *sha1, int delopt)
+int delete_ref(const char *refname, const unsigned char *sha1, unsigned int flags)
 {
 	struct ref_transaction *transaction;
 	struct strbuf err = STRBUF_INIT;
 
 	transaction = ref_transaction_begin(&err);
 	if (!transaction ||
-	    ref_transaction_delete(transaction, refname, sha1, delopt,
-				   sha1 && !is_null_sha1(sha1), NULL, &err) ||
+	    ref_transaction_delete(transaction, refname,
+				   (sha1 && !is_null_sha1(sha1)) ? sha1 : NULL,
+				   flags, NULL, &err) ||
 	    ref_transaction_commit(transaction, &err)) {
 		error("%s", err.buf);
 		ref_transaction_free(transaction);
 		strbuf_release(&err);
 		return 1;
 	}
