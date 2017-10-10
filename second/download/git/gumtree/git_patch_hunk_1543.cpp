 
 	strbuf_addf(&sb, _("%s: fast-forward"), _(action_name(opts)));
 
 	transaction = ref_transaction_begin(&err);
 	if (!transaction ||
 	    ref_transaction_update(transaction, "HEAD",
-				   to, unborn ? null_sha1 : from,
+				   to->hash, unborn ? null_sha1 : from->hash,
 				   0, sb.buf, &err) ||
 	    ref_transaction_commit(transaction, &err)) {
 		ref_transaction_free(transaction);
 		error("%s", err.buf);
 		strbuf_release(&sb);
 		strbuf_release(&err);
