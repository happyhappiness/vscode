 		have_old = 1;
 	}
 
 	if (*next != line_termination)
 		die("delete %s: extra input: %s", refname, next);
 
-	ref_transaction_delete(transaction, refname, old_sha1,
-			       update_flags, have_old);
+	if (ref_transaction_delete(transaction, refname, old_sha1,
+				   update_flags, have_old, msg, &err))
+		die("%s", err.buf);
 
 	update_flags = 0;
 	free(refname);
+	strbuf_release(&err);
 
 	return next;
 }
 
-static const char *parse_cmd_verify(struct strbuf *input, const char *next)
+static const char *parse_cmd_verify(struct ref_transaction *transaction,
+				    struct strbuf *input, const char *next)
 {
+	struct strbuf err = STRBUF_INIT;
 	char *refname;
 	unsigned char new_sha1[20];
 	unsigned char old_sha1[20];
 	int have_old;
 
 	refname = parse_refname(input, &next);
