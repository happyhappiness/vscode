 		errno = exists_in_PATH(file) ? EACCES : ENOENT;
 	else if (errno == ENOTDIR && !strchr(file, '/'))
 		errno = ENOENT;
 	return -1;
 }
 
-static const char **prepare_shell_cmd(const char **argv)
+static const char **prepare_shell_cmd(struct argv_array *out, const char **argv)
 {
-	int argc, nargc = 0;
-	const char **nargv;
-
-	for (argc = 0; argv[argc]; argc++)
-		; /* just counting */
-	/* +1 for NULL, +3 for "sh -c" plus extra $0 */
-	nargv = xmalloc(sizeof(*nargv) * (argc + 1 + 3));
-
-	if (argc < 1)
+	if (!argv[0])
 		die("BUG: shell command is empty");
 
 	if (strcspn(argv[0], "|&;<>()$`\\\"' \t\n*?[#~=%") != strlen(argv[0])) {
 #ifndef GIT_WINDOWS_NATIVE
-		nargv[nargc++] = SHELL_PATH;
+		argv_array_push(out, SHELL_PATH);
 #else
-		nargv[nargc++] = "sh";
+		argv_array_push(out, "sh");
 #endif
-		nargv[nargc++] = "-c";
+		argv_array_push(out, "-c");
 
-		if (argc < 2)
-			nargv[nargc++] = argv[0];
-		else {
-			struct strbuf arg0 = STRBUF_INIT;
-			strbuf_addf(&arg0, "%s \"$@\"", argv[0]);
-			nargv[nargc++] = strbuf_detach(&arg0, NULL);
-		}
+		/*
+		 * If we have no extra arguments, we do not even need to
+		 * bother with the "$@" magic.
+		 */
+		if (!argv[1])
+			argv_array_push(out, argv[0]);
+		else
+			argv_array_pushf(out, "%s \"$@\"", argv[0]);
 	}
 
-	for (argc = 0; argv[argc]; argc++)
-		nargv[nargc++] = argv[argc];
-	nargv[nargc] = NULL;
-
-	return nargv;
+	argv_array_pushv(out, argv);
+	return out->argv;
 }
 
 #ifndef GIT_WINDOWS_NATIVE
 static int execv_shell_cmd(const char **argv)
 {
-	const char **nargv = prepare_shell_cmd(argv);
-	trace_argv_printf(nargv, "trace: exec:");
-	sane_execvp(nargv[0], (char **)nargv);
-	free(nargv);
+	struct argv_array nargv = ARGV_ARRAY_INIT;
+	prepare_shell_cmd(&nargv, argv);
+	trace_argv_printf(nargv.argv, "trace: exec:");
+	sane_execvp(nargv.argv[0], (char **)nargv.argv);
+	argv_array_clear(&nargv);
 	return -1;
 }
 #endif
 
 #ifndef GIT_WINDOWS_NATIVE
 static int child_notifier = -1;
