 	if (want_color(s->use_color))
 		copts.nl = GIT_COLOR_RESET "\n";
 	print_columns(&output, s->colopts, &copts);
 	string_list_clear(&output, 0);
 	strbuf_release(&buf);
 conclude:
-	status_printf_ln(s, GIT_COLOR_NORMAL, "");
+	status_printf_ln(s, GIT_COLOR_NORMAL, "%s", "");
 }
 
 void wt_status_truncate_message_at_cut_line(struct strbuf *buf)
 {
 	const char *p;
 	struct strbuf pattern = STRBUF_INIT;
