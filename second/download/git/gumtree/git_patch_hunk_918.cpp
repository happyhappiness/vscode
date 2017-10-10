 		exc_given = 1;
 
 	if (require_work_tree && !is_inside_work_tree())
 		setup_work_tree();
 
 	if (recurse_submodules)
-		compile_submodule_options(&dir, show_tag);
+		compile_submodule_options(argv, &dir, show_tag);
 
 	if (recurse_submodules &&
 	    (show_stage || show_deleted || show_others || show_unmerged ||
 	     show_killed || show_modified || show_resolve_undo || with_tree))
 		die("ls-files --recurse-submodules unsupported mode");
 
