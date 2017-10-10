 		die("create %s: zero <newvalue>", refname);
 
 	if (*next != line_termination)
 		die("create %s: extra input: %s", refname, next);
 
 	if (ref_transaction_create(transaction, refname, new_sha1,
-				   update_flags, msg, &err))
+				   update_flags | create_reflog_flag,
+				   msg, &err))
 		die("%s", err.buf);
 
 	update_flags = 0;
 	free(refname);
 	strbuf_release(&err);
 
