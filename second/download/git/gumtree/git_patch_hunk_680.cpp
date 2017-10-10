 		       PATHSPEC_PREFER_CWD |
 		       (opt.max_depth != -1 ? PATHSPEC_MAXDEPTH_VALID : 0),
 		       prefix, argv + i);
 	pathspec.max_depth = opt.max_depth;
 	pathspec.recursive = 1;
 
+	if (recurse_submodules) {
+		gitmodules_config();
+		compile_submodule_options(&opt, &pathspec, cached, untracked,
+					  opt_exclude, use_index,
+					  pattern_type_arg);
+	}
+
 	if (show_in_pager && (cached || list.nr))
 		die(_("--open-files-in-pager only works on the worktree"));
 
 	if (show_in_pager && opt.pattern_list && !opt.pattern_list->next) {
 		const char *pager = path_list.items[0].string;
 		int len = strlen(pager);
