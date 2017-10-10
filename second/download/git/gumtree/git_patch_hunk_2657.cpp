 {
 	struct strbuf path = STRBUF_INIT;
 	struct stat st;
 
 	strbuf_addf(&path, "%s/gitdir", gitdir);
 	if (stat(path.buf, &st) || st.st_mtime + 24 * 3600 < time(NULL))
-		write_file(path.buf, 1, "%s\n", gitfile);
+		write_file(path.buf, "%s", gitfile);
 	strbuf_release(&path);
 }
 
 /*
  * Try to read the location of the git directory from the .git file,
  * return path to git directory if found.
+ *
+ * On failure, if return_error_code is not NULL, return_error_code
+ * will be set to an error code and NULL will be returned. If
+ * return_error_code is NULL the function will die instead (for most
+ * cases).
  */
-const char *read_gitfile(const char *path)
+const char *read_gitfile_gently(const char *path, int *return_error_code)
 {
-	char *buf;
-	char *dir;
+	const int max_file_size = 1 << 20;  /* 1MB */
+	int error_code = 0;
+	char *buf = NULL;
+	char *dir = NULL;
 	const char *slash;
 	struct stat st;
 	int fd;
 	ssize_t len;
 
-	if (stat(path, &st))
-		return NULL;
-	if (!S_ISREG(st.st_mode))
-		return NULL;
+	if (stat(path, &st)) {
+		error_code = READ_GITFILE_ERR_STAT_FAILED;
+		goto cleanup_return;
+	}
+	if (!S_ISREG(st.st_mode)) {
+		error_code = READ_GITFILE_ERR_NOT_A_FILE;
+		goto cleanup_return;
+	}
+	if (st.st_size > max_file_size) {
+		error_code = READ_GITFILE_ERR_TOO_LARGE;
+		goto cleanup_return;
+	}
 	fd = open(path, O_RDONLY);
-	if (fd < 0)
-		die_errno("Error opening '%s'", path);
+	if (fd < 0) {
+		error_code = READ_GITFILE_ERR_OPEN_FAILED;
+		goto cleanup_return;
+	}
 	buf = xmalloc(st.st_size + 1);
 	len = read_in_full(fd, buf, st.st_size);
 	close(fd);
-	if (len != st.st_size)
-		die("Error reading %s", path);
+	if (len != st.st_size) {
+		error_code = READ_GITFILE_ERR_READ_FAILED;
+		goto cleanup_return;
+	}
 	buf[len] = '\0';
-	if (!starts_with(buf, "gitdir: "))
-		die("Invalid gitfile format: %s", path);
+	if (!starts_with(buf, "gitdir: ")) {
+		error_code = READ_GITFILE_ERR_INVALID_FORMAT;
+		goto cleanup_return;
+	}
 	while (buf[len - 1] == '\n' || buf[len - 1] == '\r')
 		len--;
-	if (len < 9)
-		die("No path in gitfile: %s", path);
+	if (len < 9) {
+		error_code = READ_GITFILE_ERR_NO_PATH;
+		goto cleanup_return;
+	}
 	buf[len] = '\0';
 	dir = buf + 8;
 
 	if (!is_absolute_path(dir) && (slash = strrchr(path, '/'))) {
 		size_t pathlen = slash+1 - path;
 		size_t dirlen = pathlen + len - 8;
