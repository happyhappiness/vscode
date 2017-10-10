 	if (hold_lock_file_for_update(&credential_lock, fn, 0) < 0)
 		die_errno("unable to get credential storage lock");
 	if (extra)
 		print_line(extra);
 	parse_credential_file(fn, c, NULL, print_line);
 	if (commit_lock_file(&credential_lock) < 0)
-		die_errno("unable to commit credential store");
+		die_errno("unable to write credential store");
 }
 
 static void store_credential_file(const char *fn, struct credential *c)
 {
 	struct strbuf buf = STRBUF_INIT;
 
