 	argv_array_pushf(&sm_summary.args, "%d", s->submodule_summary);
 	if (!uncommitted)
 		argv_array_push(&sm_summary.args, s->amend ? "HEAD^" : "HEAD");
 
 	sm_summary.git_cmd = 1;
 	sm_summary.no_stdin = 1;
-	fflush(s->fp);
-	sm_summary.out = -1;
 
-	run_command(&sm_summary);
-
-	len = strbuf_read(&cmd_stdout, sm_summary.out, 1024);
+	capture_command(&sm_summary, &cmd_stdout, 1024);
 
 	/* prepend header, only if there's an actual output */
-	if (len) {
+	if (cmd_stdout.len) {
 		if (uncommitted)
 			strbuf_addstr(&summary, _("Submodules changed but not updated:"));
 		else
 			strbuf_addstr(&summary, _("Submodule changes to be committed:"));
 		strbuf_addstr(&summary, "\n\n");
 	}
 	strbuf_addbuf(&summary, &cmd_stdout);
 	strbuf_release(&cmd_stdout);
 
 	if (s->display_comment_prefix) {
+		size_t len;
 		summary_content = strbuf_detach(&summary, &len);
 		strbuf_add_commented_lines(&summary, summary_content, len);
 		free(summary_content);
 	}
 
 	fputs(summary.buf, s->fp);
