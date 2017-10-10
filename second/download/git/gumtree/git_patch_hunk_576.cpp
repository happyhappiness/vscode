 		rev.diffopt.use_color = 0;
 		wt_status_add_cut_line(s->fp);
 	}
 	if (s->verbose > 1 && s->commitable) {
 		/* print_updated() printed a header, so do we */
 		if (s->fp != stdout)
-			wt_status_print_trailer(s);
+			wt_longstatus_print_trailer(s);
 		status_printf_ln(s, c, _("Changes to be committed:"));
 		rev.diffopt.a_prefix = "c/";
 		rev.diffopt.b_prefix = "i/";
 	} /* else use prefix as per user config */
 	run_diff_index(&rev, 1);
 	if (s->verbose > 1 &&
