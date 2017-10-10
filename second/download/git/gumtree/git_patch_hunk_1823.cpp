 static void save_env(void)
 {
 	int i;
 	if (saved_environment)
 		return;
 	saved_environment = 1;
-	if (!getcwd(orig_cwd, sizeof(orig_cwd)))
-		die_errno("cannot getcwd");
+	orig_cwd = xgetcwd();
 	for (i = 0; i < ARRAY_SIZE(env_names); i++) {
 		orig_env[i] = getenv(env_names[i]);
 		if (orig_env[i])
 			orig_env[i] = xstrdup(orig_env[i]);
 	}
 }
 
 static void restore_env(void)
 {
 	int i;
-	if (*orig_cwd && chdir(orig_cwd))
+	if (orig_cwd && chdir(orig_cwd))
 		die_errno("could not move to %s", orig_cwd);
+	free(orig_cwd);
 	for (i = 0; i < ARRAY_SIZE(env_names); i++) {
 		if (orig_env[i])
 			setenv(env_names[i], orig_env[i], 1);
 		else
 			unsetenv(env_names[i]);
 	}
