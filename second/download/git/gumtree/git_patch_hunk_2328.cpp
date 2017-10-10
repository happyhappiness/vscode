  *  - either a HEAD symlink or a HEAD file that is formatted as
  *    a proper "ref:", or a regular file HEAD that has a properly
  *    formatted sha1 object name.
  */
 int is_git_directory(const char *suspect)
 {
-	char path[PATH_MAX];
-	size_t len = strlen(suspect);
+	struct strbuf path = STRBUF_INIT;
+	int ret = 0;
+	size_t len;
+
+	/* Check worktree-related signatures */
+	strbuf_addf(&path, "%s/HEAD", suspect);
+	if (validate_headref(path.buf))
+		goto done;
+
+	strbuf_reset(&path);
+	get_common_dir(&path, suspect);
+	len = path.len;
 
-	if (PATH_MAX <= len + strlen("/objects"))
-		die("Too long path: %.*s", 60, suspect);
-	strcpy(path, suspect);
+	/* Check non-worktree-related signatures */
 	if (getenv(DB_ENVIRONMENT)) {
 		if (access(getenv(DB_ENVIRONMENT), X_OK))
-			return 0;
+			goto done;
 	}
 	else {
-		strcpy(path + len, "/objects");
-		if (access(path, X_OK))
-			return 0;
+		strbuf_setlen(&path, len);
+		strbuf_addstr(&path, "/objects");
+		if (access(path.buf, X_OK))
+			goto done;
 	}
 
-	strcpy(path + len, "/refs");
-	if (access(path, X_OK))
-		return 0;
-
-	strcpy(path + len, "/HEAD");
-	if (validate_headref(path))
-		return 0;
-
-	return 1;
+	strbuf_setlen(&path, len);
+	strbuf_addstr(&path, "/refs");
+	if (access(path.buf, X_OK))
+		goto done;
+
+	ret = 1;
+done:
+	strbuf_release(&path);
+	return ret;
 }
 
 int is_inside_git_dir(void)
 {
 	if (inside_git_dir < 0)
 		inside_git_dir = is_inside_dir(get_git_dir());
