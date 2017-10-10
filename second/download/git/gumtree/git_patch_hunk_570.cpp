 		status_printf_ln(s, c, _("  (use \"git reset %s <file>...\" to unstage)"), s->reference);
 	else
 		status_printf_ln(s, c, _("  (use \"git rm --cached <file>...\" to unstage)"));
 	status_printf_ln(s, c, "%s", "");
 }
 
-static void wt_status_print_dirty_header(struct wt_status *s,
-					 int has_deleted,
-					 int has_dirty_submodules)
+static void wt_longstatus_print_dirty_header(struct wt_status *s,
+					     int has_deleted,
+					     int has_dirty_submodules)
 {
 	const char *c = color(WT_STATUS_HEADER, s);
 
 	status_printf_ln(s, c, _("Changes not staged for commit:"));
 	if (!s->hints)
 		return;
