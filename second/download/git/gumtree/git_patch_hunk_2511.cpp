 
 	if (prepare_revision_walk(&revs))
 		die(_("revision walk setup failed"));
 	commit = get_revision(&revs);
 	if (commit) {
 		struct pretty_print_context ctx = {0};
-		ctx.date_mode = DATE_NORMAL;
+		ctx.date_mode.type = DATE_NORMAL;
 		strbuf_release(&buf);
 		format_commit_message(commit, "%aN <%aE>", &buf, &ctx);
 		clear_mailmap(&mailmap);
 		return strbuf_detach(&buf, NULL);
 	}
 	die(_("--author '%s' is not 'Name <email>' and matches no existing author"), name);
