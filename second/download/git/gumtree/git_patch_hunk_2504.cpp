 };
 
 static const char *argv_submodule[] = {
 	"submodule", "update", "--init", "--recursive", NULL
 };
 
-static char *get_repo_path(const char *repo, int *is_bundle)
+static const char *get_repo_path_1(struct strbuf *path, int *is_bundle)
 {
 	static char *suffix[] = { "/.git", "", ".git/.git", ".git" };
 	static char *bundle_suffix[] = { ".bundle", "" };
+	size_t baselen = path->len;
 	struct stat st;
 	int i;
 
 	for (i = 0; i < ARRAY_SIZE(suffix); i++) {
-		const char *path;
-		path = mkpath("%s%s", repo, suffix[i]);
-		if (stat(path, &st))
+		strbuf_setlen(path, baselen);
+		strbuf_addstr(path, suffix[i]);
+		if (stat(path->buf, &st))
 			continue;
-		if (S_ISDIR(st.st_mode) && is_git_directory(path)) {
+		if (S_ISDIR(st.st_mode) && is_git_directory(path->buf)) {
 			*is_bundle = 0;
-			return xstrdup(absolute_path(path));
+			return path->buf;
 		} else if (S_ISREG(st.st_mode) && st.st_size > 8) {
 			/* Is it a "gitfile"? */
 			char signature[8];
-			int len, fd = open(path, O_RDONLY);
+			const char *dst;
+			int len, fd = open(path->buf, O_RDONLY);
 			if (fd < 0)
 				continue;
 			len = read_in_full(fd, signature, 8);
 			close(fd);
 			if (len != 8 || strncmp(signature, "gitdir: ", 8))
 				continue;
-			path = read_gitfile(path);
-			if (path) {
+			dst = read_gitfile(path->buf);
+			if (dst) {
 				*is_bundle = 0;
-				return xstrdup(absolute_path(path));
+				return dst;
 			}
 		}
 	}
 
 	for (i = 0; i < ARRAY_SIZE(bundle_suffix); i++) {
-		const char *path;
-		path = mkpath("%s%s", repo, bundle_suffix[i]);
-		if (!stat(path, &st) && S_ISREG(st.st_mode)) {
+		strbuf_setlen(path, baselen);
+		strbuf_addstr(path, bundle_suffix[i]);
+		if (!stat(path->buf, &st) && S_ISREG(st.st_mode)) {
 			*is_bundle = 1;
-			return xstrdup(absolute_path(path));
+			return path->buf;
 		}
 	}
 
 	return NULL;
 }
 
+static char *get_repo_path(const char *repo, int *is_bundle)
+{
+	struct strbuf path = STRBUF_INIT;
+	const char *raw;
+	char *canon;
+
+	strbuf_addstr(&path, repo);
+	raw = get_repo_path_1(&path, is_bundle);
+	canon = raw ? xstrdup(absolute_path(raw)) : NULL;
+	strbuf_release(&path);
+	return canon;
+}
+
 static char *guess_dir_name(const char *repo, int is_bundle, int is_bare)
 {
-	const char *end = repo + strlen(repo), *start;
+	const char *end = repo + strlen(repo), *start, *ptr;
 	size_t len;
 	char *dir;
 
 	/*
+	 * Skip scheme.
+	 */
+	start = strstr(repo, "://");
+	if (start == NULL)
+		start = repo;
+	else
+		start += 3;
+
+	/*
+	 * Skip authentication data. The stripping does happen
+	 * greedily, such that we strip up to the last '@' inside
+	 * the host part.
+	 */
+	for (ptr = start; ptr < end && !is_dir_sep(*ptr); ptr++) {
+		if (*ptr == '@')
+			start = ptr + 1;
+	}
+
+	/*
 	 * Strip trailing spaces, slashes and /.git
 	 */
-	while (repo < end && (is_dir_sep(end[-1]) || isspace(end[-1])))
+	while (start < end && (is_dir_sep(end[-1]) || isspace(end[-1])))
 		end--;
-	if (end - repo > 5 && is_dir_sep(end[-5]) &&
+	if (end - start > 5 && is_dir_sep(end[-5]) &&
 	    !strncmp(end - 4, ".git", 4)) {
 		end -= 5;
-		while (repo < end && is_dir_sep(end[-1]))
+		while (start < end && is_dir_sep(end[-1]))
 			end--;
 	}
 
 	/*
-	 * Find last component, but be prepared that repo could have
-	 * the form  "remote.example.com:foo.git", i.e. no slash
-	 * in the directory part.
+	 * Strip trailing port number if we've got only a
+	 * hostname (that is, there is no dir separator but a
+	 * colon). This check is required such that we do not
+	 * strip URI's like '/foo/bar:2222.git', which should
+	 * result in a dir '2222' being guessed due to backwards
+	 * compatibility.
+	 */
+	if (memchr(start, '/', end - start) == NULL
+	    && memchr(start, ':', end - start) != NULL) {
+		ptr = end;
+		while (start < ptr && isdigit(ptr[-1]) && ptr[-1] != ':')
+			ptr--;
+		if (start < ptr && ptr[-1] == ':')
+			end = ptr - 1;
+	}
+
+	/*
+	 * Find last component. To remain backwards compatible we
+	 * also regard colons as path separators, such that
+	 * cloning a repository 'foo:bar.git' would result in a
+	 * directory 'bar' being guessed.
 	 */
-	start = end;
-	while (repo < start && !is_dir_sep(start[-1]) && start[-1] != ':')
-		start--;
+	ptr = end;
+	while (start < ptr && !is_dir_sep(ptr[-1]) && ptr[-1] != ':')
+		ptr--;
+	start = ptr;
 
 	/*
 	 * Strip .{bundle,git}.
 	 */
 	len = end - start;
 	strip_suffix_mem(start, &len, is_bundle ? ".bundle" : ".git");
 
+	if (!len || (len == 1 && *start == '/'))
+	    die("No directory name could be guessed.\n"
+		"Please specify a directory on the command line");
+
 	if (is_bare)
 		dir = xstrfmt("%.*s.git", (int)len, start);
 	else
 		dir = xstrndup(start, len);
 	/*
 	 * Replace sequences of 'control' characters and whitespace
