  *
  * If path is our buffer, then return path, as it's already what the
  * user wants.
  */
 static const char *real_path_internal(const char *path, int die_on_error)
 {
-	static char bufs[2][PATH_MAX + 1], *buf = bufs[0], *next_buf = bufs[1];
+	static struct strbuf sb = STRBUF_INIT;
 	char *retval = NULL;
 
 	/*
 	 * If we have to temporarily chdir(), store the original CWD
 	 * here so that we can chdir() back to it at the end of the
 	 * function:
 	 */
-	char cwd[1024] = "";
-
-	int buf_index = 1;
+	struct strbuf cwd = STRBUF_INIT;
 
 	int depth = MAXDEPTH;
 	char *last_elem = NULL;
 	struct stat st;
 
 	/* We've already done it */
-	if (path == buf || path == next_buf)
+	if (path == sb.buf)
 		return path;
 
 	if (!*path) {
 		if (die_on_error)
 			die("The empty string is not a valid path");
 		else
 			goto error_out;
 	}
 
-	if (strlcpy(buf, path, PATH_MAX) >= PATH_MAX) {
-		if (die_on_error)
-			die("Too long path: %.*s", 60, path);
-		else
-			goto error_out;
-	}
+	strbuf_reset(&sb);
+	strbuf_addstr(&sb, path);
 
 	while (depth--) {
-		if (!is_directory(buf)) {
-			char *last_slash = find_last_dir_sep(buf);
+		if (!is_directory(sb.buf)) {
+			char *last_slash = find_last_dir_sep(sb.buf);
 			if (last_slash) {
 				last_elem = xstrdup(last_slash + 1);
-				last_slash[1] = '\0';
+				strbuf_setlen(&sb, last_slash - sb.buf + 1);
 			} else {
-				last_elem = xstrdup(buf);
-				*buf = '\0';
+				last_elem = xmemdupz(sb.buf, sb.len);
+				strbuf_reset(&sb);
 			}
 		}
 
-		if (*buf) {
-			if (!*cwd && !getcwd(cwd, sizeof(cwd))) {
+		if (sb.len) {
+			if (!cwd.len && strbuf_getcwd(&cwd)) {
 				if (die_on_error)
 					die_errno("Could not get current working directory");
 				else
 					goto error_out;
 			}
 
-			if (chdir(buf)) {
+			if (chdir(sb.buf)) {
 				if (die_on_error)
-					die_errno("Could not switch to '%s'", buf);
+					die_errno("Could not switch to '%s'",
+						  sb.buf);
 				else
 					goto error_out;
 			}
 		}
-		if (!getcwd(buf, PATH_MAX)) {
+		if (strbuf_getcwd(&sb)) {
 			if (die_on_error)
 				die_errno("Could not get current working directory");
 			else
 				goto error_out;
 		}
 
 		if (last_elem) {
-			size_t len = strlen(buf);
-			if (len + strlen(last_elem) + 2 > PATH_MAX) {
-				if (die_on_error)
-					die("Too long path name: '%s/%s'",
-					    buf, last_elem);
-				else
-					goto error_out;
-			}
-			if (len && !is_dir_sep(buf[len - 1]))
-				buf[len++] = '/';
-			strcpy(buf + len, last_elem);
+			if (sb.len && !is_dir_sep(sb.buf[sb.len - 1]))
+				strbuf_addch(&sb, '/');
+			strbuf_addstr(&sb, last_elem);
 			free(last_elem);
 			last_elem = NULL;
 		}
 
-		if (!lstat(buf, &st) && S_ISLNK(st.st_mode)) {
-			ssize_t len = readlink(buf, next_buf, PATH_MAX);
+		if (!lstat(sb.buf, &st) && S_ISLNK(st.st_mode)) {
+			struct strbuf next_sb = STRBUF_INIT;
+			ssize_t len = strbuf_readlink(&next_sb, sb.buf, 0);
 			if (len < 0) {
 				if (die_on_error)
-					die_errno("Invalid symlink '%s'", buf);
-				else
-					goto error_out;
-			}
-			if (PATH_MAX <= len) {
-				if (die_on_error)
-					die("symbolic link too long: %s", buf);
+					die_errno("Invalid symlink '%s'",
+						  sb.buf);
 				else
 					goto error_out;
 			}
-			next_buf[len] = '\0';
-			buf = next_buf;
-			buf_index = 1 - buf_index;
-			next_buf = bufs[buf_index];
+			strbuf_swap(&sb, &next_sb);
+			strbuf_release(&next_sb);
 		} else
 			break;
 	}
 
-	retval = buf;
+	retval = sb.buf;
 error_out:
 	free(last_elem);
-	if (*cwd && chdir(cwd))
-		die_errno("Could not change back to '%s'", cwd);
+	if (cwd.len && chdir(cwd.buf))
+		die_errno("Could not change back to '%s'", cwd.buf);
+	strbuf_release(&cwd);
 
 	return retval;
 }
 
 const char *real_path(const char *path)
 {
