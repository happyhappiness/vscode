 			die_errno(_("unable to move %s to %s"), src, git_dir);
 	}
 
 	write_file(git_link, "gitdir: %s", git_dir);
 }
 
-int init_db(const char *template_dir, unsigned int flags)
+int init_db(const char *git_dir, const char *real_git_dir,
+	    const char *template_dir, unsigned int flags)
 {
 	int reinit;
-	const char *git_dir = get_git_dir();
+	int exist_ok = flags & INIT_DB_EXIST_OK;
+	char *original_git_dir = xstrdup(real_path(git_dir));
 
-	if (git_link)
-		separate_git_dir(git_dir);
+	if (real_git_dir) {
+		struct stat st;
+
+		if (!exist_ok && !stat(git_dir, &st))
+			die(_("%s already exists"), git_dir);
+
+		if (!exist_ok && !stat(real_git_dir, &st))
+			die(_("%s already exists"), real_git_dir);
+
+		set_git_dir(real_path(real_git_dir));
+		git_dir = get_git_dir();
+		separate_git_dir(git_dir, original_git_dir);
+	}
+	else {
+		set_git_dir(real_path(git_dir));
+		git_dir = get_git_dir();
+	}
+	startup_info->have_repository = 1;
 
 	safe_create_dir(git_dir, 0);
 
 	init_is_bare_repository = is_bare_repository();
 
 	/* Check to see if the repository version is right.
 	 * Note that a newly created repository does not have
 	 * config file, so this will not fail.  What we are catching
 	 * is an attempt to reinitialize new repository with an old tool.
 	 */
 	check_repository_format();
 
-	reinit = create_default_files(template_dir);
+	reinit = create_default_files(template_dir, original_git_dir);
 
 	create_object_directory();
 
 	if (get_shared_repository()) {
 		char buf[10];
 		/* We do not spell "group" and such, so that
