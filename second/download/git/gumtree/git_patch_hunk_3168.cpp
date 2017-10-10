 {
 	if (!branch)
 		die(_(message_detached_head_die), remote->name);
 	add_refspec(branch->name);
 }
 
-static char warn_unspecified_push_default_msg[] =
-N_("push.default is unset; its implicit value has changed in\n"
-   "Git 2.0 from 'matching' to 'simple'. To squelch this message\n"
-   "and maintain the traditional behavior, use:\n"
-   "\n"
-   "  git config --global push.default matching\n"
-   "\n"
-   "To squelch this message and adopt the new behavior now, use:\n"
-   "\n"
-   "  git config --global push.default simple\n"
-   "\n"
-   "When push.default is set to 'matching', git will push local branches\n"
-   "to the remote branches that already exist with the same name.\n"
-   "\n"
-   "Since Git 2.0, Git defaults to the more conservative 'simple'\n"
-   "behavior, which only pushes the current branch to the corresponding\n"
-   "remote branch that 'git pull' uses to update the current branch.\n"
-   "\n"
-   "See 'git help config' and search for 'push.default' for further information.\n"
-   "(the 'simple' mode was introduced in Git 1.7.11. Use the similar mode\n"
-   "'current' instead of 'simple' if you sometimes use older versions of Git)");
-
-static void warn_unspecified_push_default_configuration(void)
-{
-	static int warn_once;
-
-	if (warn_once++)
-		return;
-	warning("%s\n", _(warn_unspecified_push_default_msg));
-}
-
 static int is_workflow_triangular(struct remote *remote)
 {
 	struct remote *fetch_remote = remote_get(NULL);
 	return (fetch_remote && fetch_remote != remote);
 }
 
