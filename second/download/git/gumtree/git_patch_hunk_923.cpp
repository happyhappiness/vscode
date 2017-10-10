 	args[i] = NULL;
 
 	if (run_command_v_opt(args, RUN_GIT_CMD))
 		die(_("read-tree failed"));
 }
 
-static void restore_state(const unsigned char *head,
-			  const unsigned char *stash)
+static void restore_state(const struct object_id *head,
+			  const struct object_id *stash)
 {
 	struct strbuf sb = STRBUF_INIT;
 	const char *args[] = { "stash", "apply", NULL, NULL };
 
-	if (is_null_sha1(stash))
+	if (is_null_oid(stash))
 		return;
 
-	reset_hard(head, 1);
+	reset_hard(head->hash, 1);
 
-	args[2] = sha1_to_hex(stash);
+	args[2] = oid_to_hex(stash);
 
 	/*
 	 * It is OK to ignore error here, for example when there was
 	 * nothing to restore.
 	 */
 	run_command_v_opt(args, RUN_GIT_CMD);
