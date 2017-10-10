 
 	if (!use_index && (untracked || cached))
 		die(_("--cached or --untracked cannot be used with --no-index."));
 
 	if (!use_index || untracked) {
 		int use_exclude = (opt_exclude < 0) ? use_index : !!opt_exclude;
-		if (list.nr)
-			die(_("--no-index or --untracked cannot be used with revs."));
 		hit = grep_directory(&opt, &pathspec, use_exclude, use_index);
 	} else if (0 <= opt_exclude) {
 		die(_("--[no-]exclude-standard cannot be used for tracked contents."));
 	} else if (!list.nr) {
 		if (!cached)
 			setup_work_tree();
