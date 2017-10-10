 	else
 		status_printf_ln(s, color,
 				 _("You are currently bisecting."));
 	if (s->hints)
 		status_printf_ln(s, color,
 			_("  (use \"git bisect reset\" to get back to the original branch)"));
-	wt_status_print_trailer(s);
+	wt_longstatus_print_trailer(s);
 }
 
 /*
  * Extract branch information from rebase/bisect
  */
 static char *get_branch(const struct worktree *wt, const char *path)
