 	free(state.branch);
 	free(state.onto);
 	free(state.detached_from);
 
 	if (s->is_initial) {
 		status_printf_ln(s, color(WT_STATUS_HEADER, s), "%s", "");
-		status_printf_ln(s, color(WT_STATUS_HEADER, s), _("Initial commit"));
+		status_printf_ln(s, color(WT_STATUS_HEADER, s),
+				 s->commit_template
+				 ? _("Initial commit")
+				 : _("No commits yet"));
 		status_printf_ln(s, color(WT_STATUS_HEADER, s), "%s", "");
 	}
 
 	wt_longstatus_print_updated(s);
 	wt_longstatus_print_unmerged(s);
 	wt_longstatus_print_changed(s);
