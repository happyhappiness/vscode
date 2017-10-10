 		strbuf_addch(&sb, '\n');
 	strbuf_insert(&sb, 0, reflog_msg, strlen(reflog_msg));
 	strbuf_insert(&sb, strlen(reflog_msg), ": ", 2);
 
 	transaction = ref_transaction_begin(&err);
 	if (!transaction ||
-	    ref_transaction_update(transaction, "HEAD", sha1,
+	    ref_transaction_update(transaction, "HEAD", oid.hash,
 				   current_head
 				   ? current_head->object.oid.hash : null_sha1,
 				   0, sb.buf, &err) ||
 	    ref_transaction_commit(transaction, &err)) {
 		rollback_index_files();
 		die("%s", err.buf);
