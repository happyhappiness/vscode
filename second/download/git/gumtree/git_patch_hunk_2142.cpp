 		git_dir = xstrdup(dir);
 	else {
 		work_tree = dir;
 		git_dir = mkpathdup("%s/.git", dir);
 	}
 
+	atexit(remove_junk);
+	sigchain_push_common(remove_junk_on_signal);
+
 	if (!option_bare) {
-		junk_work_tree = work_tree;
 		if (safe_create_leading_directories_const(work_tree) < 0)
 			die_errno(_("could not create leading directories of '%s'"),
 				  work_tree);
 		if (!dest_exists && mkdir(work_tree, 0777))
-			die_errno(_("could not create work tree dir '%s'."),
+			die_errno(_("could not create work tree dir '%s'"),
 				  work_tree);
+		junk_work_tree = work_tree;
 		set_git_work_tree(work_tree);
 	}
-	junk_git_dir = git_dir;
-	atexit(remove_junk);
-	sigchain_push_common(remove_junk_on_signal);
 
+	junk_git_dir = git_dir;
 	if (safe_create_leading_directories_const(git_dir) < 0)
 		die(_("could not create leading directories of '%s'"), git_dir);
 
 	set_git_dir_init(git_dir, real_git_dir, 0);
 	if (real_git_dir) {
 		git_dir = real_git_dir;
