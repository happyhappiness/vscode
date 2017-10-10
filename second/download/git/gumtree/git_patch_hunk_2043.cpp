 			cmd->error_string = "deny deleting a hidden ref";
 		else
 			cmd->error_string = "deny updating a hidden ref";
 	}
 }
 
+static int should_process_cmd(struct command *cmd)
+{
+	return !cmd->error_string && !cmd->skip_update;
+}
+
+static void warn_if_skipped_connectivity_check(struct command *commands,
+					       struct shallow_info *si)
+{
+	struct command *cmd;
+	int checked_connectivity = 1;
+
+	for (cmd = commands; cmd; cmd = cmd->next) {
+		if (should_process_cmd(cmd) && si->shallow_ref[cmd->index]) {
+			error("BUG: connectivity check has not been run on ref %s",
+			      cmd->ref_name);
+			checked_connectivity = 0;
+		}
+	}
+	if (!checked_connectivity)
+		die("BUG: connectivity check skipped???");
+}
+
+static void execute_commands_non_atomic(struct command *commands,
+					struct shallow_info *si)
+{
+	struct command *cmd;
+	struct strbuf err = STRBUF_INIT;
+
+	for (cmd = commands; cmd; cmd = cmd->next) {
+		if (!should_process_cmd(cmd))
+			continue;
+
+		transaction = ref_transaction_begin(&err);
+		if (!transaction) {
+			rp_error("%s", err.buf);
+			strbuf_reset(&err);
+			cmd->error_string = "transaction failed to start";
+			continue;
+		}
+
+		cmd->error_string = update(cmd, si);
+
+		if (!cmd->error_string
+		    && ref_transaction_commit(transaction, &err)) {
+			rp_error("%s", err.buf);
+			strbuf_reset(&err);
+			cmd->error_string = "failed to update ref";
+		}
+		ref_transaction_free(transaction);
+	}
+	strbuf_release(&err);
+}
+
+static void execute_commands_atomic(struct command *commands,
+					struct shallow_info *si)
+{
+	struct command *cmd;
+	struct strbuf err = STRBUF_INIT;
+	const char *reported_error = "atomic push failure";
+
+	transaction = ref_transaction_begin(&err);
+	if (!transaction) {
+		rp_error("%s", err.buf);
+		strbuf_reset(&err);
+		reported_error = "transaction failed to start";
+		goto failure;
+	}
+
+	for (cmd = commands; cmd; cmd = cmd->next) {
+		if (!should_process_cmd(cmd))
+			continue;
+
+		cmd->error_string = update(cmd, si);
+
+		if (cmd->error_string)
+			goto failure;
+	}
+
+	if (ref_transaction_commit(transaction, &err)) {
+		rp_error("%s", err.buf);
+		reported_error = "atomic transaction failed";
+		goto failure;
+	}
+	goto cleanup;
+
+failure:
+	for (cmd = commands; cmd; cmd = cmd->next)
+		if (!cmd->error_string)
+			cmd->error_string = reported_error;
+
+cleanup:
+	ref_transaction_free(transaction);
+	strbuf_release(&err);
+}
+
 static void execute_commands(struct command *commands,
 			     const char *unpacker_error,
 			     struct shallow_info *si)
 {
-	int checked_connectivity;
 	struct command *cmd;
 	unsigned char sha1[20];
 	struct iterate_data data;
 
 	if (unpacker_error) {
 		for (cmd = commands; cmd; cmd = cmd->next)
