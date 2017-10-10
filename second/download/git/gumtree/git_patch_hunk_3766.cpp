 
 	if (opt->add_signoff)
 		append_signoff(&msgbuf, 0, APPEND_SIGNOFF_DEDUP);
 
 	if ((ctx.fmt != CMIT_FMT_USERFORMAT) &&
 	    ctx.notes_message && *ctx.notes_message) {
-		if (ctx.fmt == CMIT_FMT_EMAIL) {
+		if (cmit_fmt_is_mail(ctx.fmt)) {
 			strbuf_addstr(&msgbuf, "---\n");
 			opt->shown_dashes = 1;
 		}
 		strbuf_addstr(&msgbuf, ctx.notes_message);
 	}
 
 	if (opt->show_log_size) {
-		printf("log size %i\n", (int)msgbuf.len);
+		fprintf(opt->diffopt.file, "log size %i\n", (int)msgbuf.len);
 		graph_show_oneline(opt->graph);
 	}
 
 	/*
 	 * Set opt->missing_newline if msgbuf doesn't
 	 * end in a newline (including if it is empty)
