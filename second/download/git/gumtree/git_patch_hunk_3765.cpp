 	graph_show_commit(opt->graph);
 
 	/*
 	 * Print header line of header..
 	 */
 
-	if (opt->commit_format == CMIT_FMT_EMAIL) {
+	if (cmit_fmt_is_mail(opt->commit_format)) {
 		log_write_email_headers(opt, commit, &ctx.subject, &extra_headers,
 					&ctx.need_8bit_cte);
 	} else if (opt->commit_format != CMIT_FMT_USERFORMAT) {
-		fputs(diff_get_color_opt(&opt->diffopt, DIFF_COMMIT), stdout);
+		fputs(diff_get_color_opt(&opt->diffopt, DIFF_COMMIT), opt->diffopt.file);
 		if (opt->commit_format != CMIT_FMT_ONELINE)
-			fputs("commit ", stdout);
+			fputs("commit ", opt->diffopt.file);
 
 		if (!opt->graph)
 			put_revision_mark(opt, commit);
 		fputs(find_unique_abbrev(commit->object.oid.hash, abbrev_commit),
-		      stdout);
+		      opt->diffopt.file);
 		if (opt->print_parents)
-			show_parents(commit, abbrev_commit);
+			show_parents(commit, abbrev_commit, opt->diffopt.file);
 		if (opt->children.name)
 			show_children(opt, commit, abbrev_commit);
 		if (parent)
-			printf(" (from %s)",
+			fprintf(opt->diffopt.file, " (from %s)",
 			       find_unique_abbrev(parent->object.oid.hash,
 						  abbrev_commit));
-		fputs(diff_get_color_opt(&opt->diffopt, DIFF_RESET), stdout);
+		fputs(diff_get_color_opt(&opt->diffopt, DIFF_RESET), opt->diffopt.file);
 		show_decorations(opt, commit);
 		if (opt->commit_format == CMIT_FMT_ONELINE) {
-			putchar(' ');
+			putc(' ', opt->diffopt.file);
 		} else {
-			putchar('\n');
+			putc('\n', opt->diffopt.file);
 			graph_show_oneline(opt->graph);
 		}
 		if (opt->reflog_info) {
 			/*
 			 * setup_revisions() ensures that opt->reflog_info
 			 * and opt->graph cannot both be set,
