 			rp_error("failed to delete %s", name);
 			return "failed to delete";
 		}
 		return NULL; /* good */
 	}
 	else {
+		struct strbuf err = STRBUF_INIT;
+		struct ref_transaction *transaction;
+
 		if (shallow_update && si->shallow_ref[cmd->index] &&
 		    update_shallow_ref(cmd, si))
 			return "shallow error";
 
-		lock = lock_any_ref_for_update(namespaced_name, old_sha1,
-					       0, NULL);
-		if (!lock) {
-			rp_error("failed to lock %s", name);
-			return "failed to lock";
-		}
-		if (write_ref_sha1(lock, new_sha1, "push")) {
-			return "failed to write"; /* error() already called */
+		transaction = ref_transaction_begin(&err);
+		if (!transaction ||
+		    ref_transaction_update(transaction, namespaced_name,
+					   new_sha1, old_sha1, 0, 1, "push",
+					   &err) ||
+		    ref_transaction_commit(transaction, &err)) {
+			ref_transaction_free(transaction);
+
+			rp_error("%s", err.buf);
+			strbuf_release(&err);
+			return "failed to update ref";
 		}
+
+		ref_transaction_free(transaction);
+		strbuf_release(&err);
 		return NULL; /* good */
 	}
 }
 
 static void run_update_post_hook(struct command *commands)
 {
 	struct command *cmd;
 	int argc;
 	const char **argv;
-	struct child_process proc;
+	struct child_process proc = CHILD_PROCESS_INIT;
 	char *hook;
 
 	hook = find_hook("post-update");
 	for (argc = 0, cmd = commands; cmd; cmd = cmd->next) {
 		if (cmd->error_string || cmd->did_not_exist)
 			continue;
