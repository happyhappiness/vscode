 		else
 			status_printf_ln(s, color,
 				_("  (all conflicts fixed: run \"git cherry-pick --continue\")"));
 		status_printf_ln(s, color,
 			_("  (use \"git cherry-pick --abort\" to cancel the cherry-pick operation)"));
 	}
-	wt_status_print_trailer(s);
+	wt_longstatus_print_trailer(s);
 }
 
 static void show_revert_in_progress(struct wt_status *s,
 					struct wt_status_state *state,
 					const char *color)
 {
