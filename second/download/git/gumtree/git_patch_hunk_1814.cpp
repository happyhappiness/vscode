 	/* foo[/]bar vs foo[] */
 	return is_dir_sep(*subdir) ? offset + 1 : -1;
 }
 
 int is_inside_dir(const char *dir)
 {
-	char cwd[PATH_MAX];
+	char *cwd;
+	int rc;
+
 	if (!dir)
 		return 0;
-	if (!getcwd(cwd, sizeof(cwd)))
-		die_errno("can't find the current directory");
-	return dir_inside_of(cwd, dir) >= 0;
+
+	cwd = xgetcwd();
+	rc = (dir_inside_of(cwd, dir) >= 0);
+	free(cwd);
+	return rc;
 }
 
 int is_empty_dir(const char *path)
 {
 	DIR *dir = opendir(path);
 	struct dirent *e;
