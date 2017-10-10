 		if (cache_tree_update(&the_index, 0))
 			return error(_("unable to update cache tree\n"));
 
 	return !hashcmp(active_cache_tree->sha1, head_commit->tree->object.oid.hash);
 }
 
+static int write_author_script(const char *message)
+{
+	struct strbuf buf = STRBUF_INIT;
+	const char *eol;
+	int res;
+
+	for (;;)
+		if (!*message || starts_with(message, "\n")) {
+missing_author:
+			/* Missing 'author' line? */
+			unlink(rebase_path_author_script());
+			return 0;
+		} else if (skip_prefix(message, "author ", &message))
+			break;
+		else if ((eol = strchr(message, '\n')))
+			message = eol + 1;
+		else
+			goto missing_author;
+
+	strbuf_addstr(&buf, "GIT_AUTHOR_NAME='");
+	while (*message && *message != '\n' && *message != '\r')
+		if (skip_prefix(message, " <", &message))
+			break;
+		else if (*message != '\'')
+			strbuf_addch(&buf, *(message++));
+		else
+			strbuf_addf(&buf, "'\\\\%c'", *(message++));
+	strbuf_addstr(&buf, "'\nGIT_AUTHOR_EMAIL='");
+	while (*message && *message != '\n' && *message != '\r')
+		if (skip_prefix(message, "> ", &message))
+			break;
+		else if (*message != '\'')
+			strbuf_addch(&buf, *(message++));
+		else
+			strbuf_addf(&buf, "'\\\\%c'", *(message++));
+	strbuf_addstr(&buf, "'\nGIT_AUTHOR_DATE='@");
+	while (*message && *message != '\n' && *message != '\r')
+		if (*message != '\'')
+			strbuf_addch(&buf, *(message++));
+		else
+			strbuf_addf(&buf, "'\\\\%c'", *(message++));
+	res = write_message(buf.buf, buf.len, rebase_path_author_script(), 1);
+	strbuf_release(&buf);
+	return res;
+}
+
 /*
- * Read the author-script file into an environment block, ready for use in
- * run_command(), that can be free()d afterwards.
+ * Read a list of environment variable assignments (such as the author-script
+ * file) into an environment block. Returns -1 on error, 0 otherwise.
  */
-static char **read_author_script(void)
+static int read_env_script(struct argv_array *env)
 {
 	struct strbuf script = STRBUF_INIT;
 	int i, count = 0;
-	char *p, *p2, **env;
-	size_t env_size;
+	char *p, *p2;
 
 	if (strbuf_read_file(&script, rebase_path_author_script(), 256) <= 0)
-		return NULL;
+		return -1;
 
 	for (p = script.buf; *p; p++)
 		if (skip_prefix(p, "'\\\\''", (const char **)&p2))
 			strbuf_splice(&script, p - script.buf, p2 - p, "'", 1);
 		else if (*p == '\'')
 			strbuf_splice(&script, p-- - script.buf, 1, "", 0);
 		else if (*p == '\n') {
 			*p = '\0';
 			count++;
 		}
 
-	env_size = (count + 1) * sizeof(*env);
-	strbuf_grow(&script, env_size);
-	memmove(script.buf + env_size, script.buf, script.len);
-	p = script.buf + env_size;
-	env = (char **)strbuf_detach(&script, NULL);
-
-	for (i = 0; i < count; i++) {
-		env[i] = p;
+	for (i = 0, p = script.buf; i < count; i++) {
+		argv_array_push(env, p);
 		p += strlen(p) + 1;
 	}
-	env[count] = NULL;
 
-	return env;
+	return 0;
 }
 
 static const char staged_changes_advice[] =
 N_("you have staged changes in your working tree\n"
 "If these changes are meant to be squashed into the previous commit, run:\n"
 "\n"
