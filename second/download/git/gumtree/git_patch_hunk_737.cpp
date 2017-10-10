 
 	return 0;
 }
 
 static const char *action_name(const struct replay_opts *opts)
 {
-	return opts->action == REPLAY_REVERT ? N_("revert") : N_("cherry-pick");
+	switch (opts->action) {
+	case REPLAY_REVERT:
+		return N_("revert");
+	case REPLAY_PICK:
+		return N_("cherry-pick");
+	case REPLAY_INTERACTIVE_REBASE:
+		return N_("rebase -i");
+	}
+	die(_("Unknown action: %d"), opts->action);
 }
 
 struct commit_message {
 	char *parent_label;
 	char *label;
 	char *subject;
