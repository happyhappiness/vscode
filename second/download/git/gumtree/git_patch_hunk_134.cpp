 	argc = parse_options(argc, argv, prefix, options, git_update_ref_usage,
 			     0);
 	if (msg && !*msg)
 		die("Refusing to perform update with empty message.");
 
 	if (read_stdin) {
+		transaction = ref_transaction_begin();
 		if (delete || no_deref || argc > 0)
 			usage_with_options(git_update_ref_usage, options);
 		if (end_null)
 			line_termination = '\0';
 		update_refs_stdin();
-		return update_refs(msg, updates, updates_count, DIE_ON_ERR);
+		if (ref_transaction_commit(transaction, msg, &err))
+			die("%s", err.buf);
+		ref_transaction_free(transaction);
+		return 0;
 	}
 
 	if (end_null)
 		usage_with_options(git_update_ref_usage, options);
 
 	if (delete) {
