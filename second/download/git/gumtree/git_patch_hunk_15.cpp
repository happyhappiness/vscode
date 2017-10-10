 	if (DIFF_OPT_TST(options, QUICK)) {
 		options->output_format = DIFF_FORMAT_NO_OUTPUT;
 		DIFF_OPT_SET(options, EXIT_WITH_STATUS);
 	}
 
 	options->diff_path_counter = 0;
+
+	if (DIFF_OPT_TST(options, FOLLOW_RENAMES) && options->pathspec.nr != 1)
+		die(_("--follow requires exactly one pathspec"));
 }
 
 static int opt_arg(const char *arg, int arg_short, const char *arg_long, int *val)
 {
 	char c, *eq;
 	int len;
