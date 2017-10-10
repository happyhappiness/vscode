 	strbuf_addf(&sb, "%s: fast-forward", action_name(opts));
 
 	transaction = ref_transaction_begin(&err);
 	if (!transaction ||
 	    ref_transaction_update(transaction, "HEAD",
 				   to, unborn ? null_sha1 : from,
-				   0, 1, sb.buf, &err) ||
+				   0, sb.buf, &err) ||
 	    ref_transaction_commit(transaction, &err)) {
 		ref_transaction_free(transaction);
 		error("%s", err.buf);
 		strbuf_release(&sb);
 		strbuf_release(&err);
 		return -1;
