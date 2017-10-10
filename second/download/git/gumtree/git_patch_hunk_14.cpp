 		diffcore_std(&diffopts);
 		paths = intersect_paths(paths, i, num_parent);
 
 		if (show_log_first && i == 0) {
 			show_log(rev);
 
-			if (rev->verbose_header && opt->output_format)
+			if (rev->verbose_header && opt->output_format &&
+			    opt->output_format != DIFF_FORMAT_NO_OUTPUT)
 				printf("%s%c", diff_line_prefix(opt),
 				       opt->line_termination);
 		}
 
 		/* if showing diff, show it in requested order */
 		if (diffopts.output_format != DIFF_FORMAT_NO_OUTPUT &&
