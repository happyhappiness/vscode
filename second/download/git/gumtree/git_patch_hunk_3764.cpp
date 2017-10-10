 	opt->loginfo = NULL;
 	if (!opt->verbose_header) {
 		graph_show_commit(opt->graph);
 
 		if (!opt->graph)
 			put_revision_mark(opt, commit);
-		fputs(find_unique_abbrev(commit->object.oid.hash, abbrev_commit), stdout);
+		fputs(find_unique_abbrev(commit->object.oid.hash, abbrev_commit), opt->diffopt.file);
 		if (opt->print_parents)
-			show_parents(commit, abbrev_commit);
+			show_parents(commit, abbrev_commit, opt->diffopt.file);
 		if (opt->children.name)
 			show_children(opt, commit, abbrev_commit);
 		show_decorations(opt, commit);
 		if (opt->graph && !graph_is_commit_finished(opt->graph)) {
-			putchar('\n');
+			putc('\n', opt->diffopt.file);
 			graph_show_remainder(opt->graph);
 		}
-		putchar(opt->diffopt.line_termination);
+		putc(opt->diffopt.line_termination, opt->diffopt.file);
 		return;
 	}
 
 	/*
 	 * If use_terminator is set, we already handled any record termination
 	 * at the end of the last record.
