 		update_flags |= REF_NODEREF;
 	else
 		die("option unknown: %s", next);
 	return next + 8;
 }
 
-static void update_refs_stdin(void)
+static void update_refs_stdin(struct ref_transaction *transaction)
 {
 	struct strbuf input = STRBUF_INIT;
 	const char *next;
 
 	if (strbuf_read(&input, 0, 1000) < 0)
 		die_errno("could not read from stdin");
