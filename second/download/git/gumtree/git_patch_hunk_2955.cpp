 	opt->loginfo = NULL;
 	if (!opt->verbose_header) {
 		graph_show_commit(opt->graph);
 
 		if (!opt->graph)
 			put_revision_mark(opt, commit);
-		fputs(find_unique_abbrev(commit->object.sha1, abbrev_commit), stdout);
+		fputs(find_unique_abbrev(commit->object.oid.hash, abbrev_commit), stdout);
 		if (opt->print_parents)
 			show_parents(commit, abbrev_commit);
 		if (opt->children.name)
 			show_children(opt, commit, abbrev_commit);
 		show_decorations(opt, commit);
 		if (opt->graph && !graph_is_commit_finished(opt->graph)) {
