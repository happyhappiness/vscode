 	if (!is_inside_work_tree() || is_inside_git_dir())
 		return;
 	if (*arg == '-')
 		return; /* flag */
 	if (!check_filename(prefix, arg))
 		return;
-	die("ambiguous argument '%s': both revision and filename\n"
-	    "Use '--' to separate paths from revisions, like this:\n"
-	    "'git <command> [<revision>...] -- [<file>...]'", arg);
+	die(_("ambiguous argument '%s': both revision and filename\n"
+	      "Use '--' to separate paths from revisions, like this:\n"
+	      "'git <command> [<revision>...] -- [<file>...]'"), arg);
 }
 
 int get_common_dir(struct strbuf *sb, const char *gitdir)
 {
 	const char *git_env_common_dir = getenv(GIT_COMMON_DIR_ENVIRONMENT);
 	if (git_env_common_dir) {
