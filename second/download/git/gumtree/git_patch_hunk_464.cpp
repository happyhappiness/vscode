 		}
 	}
 	return 1;
 }
 
 static const char rename_limit_warning[] =
-"inexact rename detection was skipped due to too many files.";
+N_("inexact rename detection was skipped due to too many files.");
 
 static const char degrade_cc_to_c_warning[] =
-"only found copies from modified paths due to too many files.";
+N_("only found copies from modified paths due to too many files.");
 
 static const char rename_limit_advice[] =
-"you may want to set your %s variable to at least "
-"%d and retry the command.";
+N_("you may want to set your %s variable to at least "
+   "%d and retry the command.");
 
 void diff_warn_rename_limit(const char *varname, int needed, int degraded_cc)
 {
 	if (degraded_cc)
-		warning(degrade_cc_to_c_warning);
+		warning(_(degrade_cc_to_c_warning));
 	else if (needed)
-		warning(rename_limit_warning);
+		warning(_(rename_limit_warning));
 	else
 		return;
 	if (0 < needed && needed < 32767)
-		warning(rename_limit_advice, varname, needed);
+		warning(_(rename_limit_advice), varname, needed);
 }
 
 void diff_flush(struct diff_options *options)
 {
 	struct diff_queue_struct *q = &diff_queued_diff;
 	int i, output_format = options->output_format;
