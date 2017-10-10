 }
 
 static const char *update(struct command *cmd, struct shallow_info *si)
 {
 	const char *name = cmd->ref_name;
 	struct strbuf namespaced_name_buf = STRBUF_INIT;
-	const char *namespaced_name, *ret;
+	static char *namespaced_name;
+	const char *ret;
 	struct object_id *old_oid = &cmd->old_oid;
 	struct object_id *new_oid = &cmd->new_oid;
 
 	/* only refs/... are allowed */
 	if (!starts_with(name, "refs/") || check_refname_format(name + 5, 0)) {
 		rp_error("refusing to create funny ref '%s' remotely", name);
 		return "funny refname";
 	}
 
 	strbuf_addf(&namespaced_name_buf, "%s%s", get_git_namespace(), name);
+	free(namespaced_name);
 	namespaced_name = strbuf_detach(&namespaced_name_buf, NULL);
 
 	if (is_ref_checked_out(namespaced_name)) {
 		switch (deny_current_branch) {
 		case DENY_IGNORE:
 			break;
