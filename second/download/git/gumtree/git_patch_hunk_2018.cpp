 		ctx.date_mode = DATE_NORMAL;
 		strbuf_release(&buf);
 		format_commit_message(commit, "%aN <%aE>", &buf, &ctx);
 		clear_mailmap(&mailmap);
 		return strbuf_detach(&buf, NULL);
 	}
-	die(_("No existing author found with '%s'"), name);
+	die(_("--author '%s' is not 'Name <email>' and matches no existing author"), name);
 }
 
 
 static void handle_untracked_files_arg(struct wt_status *s)
 {
 	if (!untracked_files_arg)
