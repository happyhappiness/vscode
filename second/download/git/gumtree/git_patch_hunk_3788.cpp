 	if (!*pager || !strcmp(pager, "cat"))
 		pager = NULL;
 
 	return pager;
 }
 
+static void setup_pager_env(struct argv_array *env)
+{
+	const char **argv;
+	int i;
+	char *pager_env = xstrdup(PAGER_ENV);
+	int n = split_cmdline(pager_env, &argv);
+
+	if (n < 0)
+		die("malformed build-time PAGER_ENV: %s",
+			split_cmdline_strerror(n));
+
+	for (i = 0; i < n; i++) {
+		char *cp = strchr(argv[i], '=');
+
+		if (!cp)
+			die("malformed build-time PAGER_ENV");
+
+		*cp = '\0';
+		if (!getenv(argv[i])) {
+			*cp = '=';
+			argv_array_push(env, argv[i]);
+		}
+	}
+	free(pager_env);
+	free(argv);
+}
+
 void prepare_pager_args(struct child_process *pager_process, const char *pager)
 {
 	argv_array_push(&pager_process->args, pager);
 	pager_process->use_shell = 1;
-	if (!getenv("LESS"))
-		argv_array_push(&pager_process->env_array, "LESS=FRX");
-	if (!getenv("LV"))
-		argv_array_push(&pager_process->env_array, "LV=-c");
+	setup_pager_env(&pager_process->env_array);
 }
 
 void setup_pager(void)
 {
 	const char *pager = git_pager(isatty(1));
 
