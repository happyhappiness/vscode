 				_("  (fix conflicts and then run \"git am --continue\")"));
 		status_printf_ln(s, color,
 			_("  (use \"git am --skip\" to skip this patch)"));
 		status_printf_ln(s, color,
 			_("  (use \"git am --abort\" to restore the original branch)"));
 	}
-	wt_status_print_trailer(s);
+	wt_longstatus_print_trailer(s);
 }
 
 static char *read_line_from_git_path(const char *filename)
 {
 	struct strbuf buf = STRBUF_INIT;
 	FILE *fp = fopen(git_path("%s", filename), "r");
