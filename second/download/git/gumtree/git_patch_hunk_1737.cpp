 			bad = _("multiple sources for the same target");
 		else if (is_dir_sep(dst[strlen(dst) - 1]))
 			bad = _("destination directory does not exist");
 		else
 			string_list_insert(&src_for_dst, dst);
 
-		if (bad) {
-			if (ignore_errors) {
-				if (--argc > 0) {
-					memmove(source + i, source + i + 1,
-						(argc - i) * sizeof(char *));
-					memmove(destination + i,
-						destination + i + 1,
-						(argc - i) * sizeof(char *));
-					memmove(modes + i, modes + i + 1,
-						(argc - i) * sizeof(enum update_mode));
-					memmove(submodule_gitfile + i,
-						submodule_gitfile + i + 1,
-						(argc - i) * sizeof(char *));
-					i--;
-				}
-			} else
-				die (_("%s, source=%s, destination=%s"),
-				     bad, src, dst);
+		if (!bad)
+			continue;
+		if (!ignore_errors)
+			die(_("%s, source=%s, destination=%s"),
+			     bad, src, dst);
+		if (--argc > 0) {
+			int n = argc - i;
+			memmove(source + i, source + i + 1,
+				n * sizeof(char *));
+			memmove(destination + i, destination + i + 1,
+				n * sizeof(char *));
+			memmove(modes + i, modes + i + 1,
+				n * sizeof(enum update_mode));
+			memmove(submodule_gitfile + i, submodule_gitfile + i + 1,
+				n * sizeof(char *));
+			i--;
 		}
 	}
 
 	for (i = 0; i < argc; i++) {
 		const char *src = source[i], *dst = destination[i];
 		enum update_mode mode = modes[i];
 		int pos;
 		if (show_only || verbose)
 			printf(_("Renaming %s to %s\n"), src, dst);
 		if (!show_only && mode != INDEX) {
 			if (rename(src, dst) < 0 && !ignore_errors)
-				die_errno (_("renaming '%s' failed"), src);
+				die_errno(_("renaming '%s' failed"), src);
 			if (submodule_gitfile[i]) {
 				if (submodule_gitfile[i] != SUBMODULE_WITH_GITDIR)
 					connect_work_tree_and_git_dir(dst, submodule_gitfile[i]);
 				if (!update_path_in_gitmodules(src, dst))
 					gitmodules_modified = 1;
 			}
