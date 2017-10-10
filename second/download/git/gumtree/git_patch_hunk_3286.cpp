 	for (i = 0; i < argc; i++) {
 		const char *src = source[i], *dst = destination[i];
 		enum update_mode mode = modes[i];
 		int pos;
 		if (show_only || verbose)
 			printf(_("Renaming %s to %s\n"), src, dst);
-		if (!show_only && mode != INDEX) {
-			if (rename(src, dst) < 0 && !ignore_errors)
-				die_errno(_("renaming '%s' failed"), src);
-			if (submodule_gitfile[i]) {
-				if (submodule_gitfile[i] != SUBMODULE_WITH_GITDIR)
-					connect_work_tree_and_git_dir(dst, submodule_gitfile[i]);
-				if (!update_path_in_gitmodules(src, dst))
-					gitmodules_modified = 1;
-			}
+		if (show_only)
+			continue;
+		if (mode != INDEX && rename(src, dst) < 0) {
+			if (ignore_errors)
+				continue;
+			die_errno(_("renaming '%s' failed"), src);
+		}
+		if (submodule_gitfile[i]) {
+			if (submodule_gitfile[i] != SUBMODULE_WITH_GITDIR)
+				connect_work_tree_and_git_dir(dst, submodule_gitfile[i]);
+			if (!update_path_in_gitmodules(src, dst))
+				gitmodules_modified = 1;
 		}
 
 		if (mode == WORKING_DIRECTORY)
 			continue;
 
 		pos = cache_name_pos(src, strlen(src));
