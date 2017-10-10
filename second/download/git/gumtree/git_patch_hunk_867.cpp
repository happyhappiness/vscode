 
 	if (conflict_style) {
 		opts.merge = 1; /* implied */
 		git_xmerge_config("merge.conflictstyle", conflict_style, NULL);
 	}
 
+	if (recurse_submodules != RECURSE_SUBMODULES_OFF) {
+		git_config(submodule_config, NULL);
+		if (recurse_submodules != RECURSE_SUBMODULES_DEFAULT)
+			set_config_update_recurse_submodules(recurse_submodules);
+	}
+
 	if ((!!opts.new_branch + !!opts.new_branch_force + !!opts.new_orphan_branch) > 1)
 		die(_("-b, -B and --orphan are mutually exclusive"));
 
 	/*
 	 * From here on, new_branch will contain the branch to be checked out,
 	 * and new_branch_force and new_orphan_branch will tell us which one of
