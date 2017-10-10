 
 	if (*next != line_termination)
 		die("update %s: extra input: %s", refname, next);
 
 	if (ref_transaction_update(transaction, refname,
 				   new_sha1, have_old ? old_sha1 : NULL,
-				   update_flags, msg, &err))
+				   update_flags | create_reflog_flag,
+				   msg, &err))
 		die("%s", err.buf);
 
 	update_flags = 0;
 	free(refname);
 	strbuf_release(&err);
 
