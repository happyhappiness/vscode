 	GIT_DIR_ENVIRONMENT,
 	GIT_WORK_TREE_ENVIRONMENT,
 	GIT_IMPLICIT_WORK_TREE_ENVIRONMENT,
 	GIT_PREFIX_ENVIRONMENT
 };
 static char *orig_env[4];
-static int saved_environment;
+static int save_restore_env_balance;
 
-static void save_env(void)
+static void save_env_before_alias(void)
 {
 	int i;
-	if (saved_environment)
-		return;
-	saved_environment = 1;
+
+	assert(save_restore_env_balance == 0);
+	save_restore_env_balance = 1;
 	orig_cwd = xgetcwd();
 	for (i = 0; i < ARRAY_SIZE(env_names); i++) {
 		orig_env[i] = getenv(env_names[i]);
 		if (orig_env[i])
 			orig_env[i] = xstrdup(orig_env[i]);
 	}
 }
 
-static void restore_env(void)
+static void restore_env(int external_alias)
 {
 	int i;
-	if (orig_cwd && chdir(orig_cwd))
+
+	assert(save_restore_env_balance == 1);
+	save_restore_env_balance = 0;
+	if (!external_alias && orig_cwd && chdir(orig_cwd))
 		die_errno("could not move to %s", orig_cwd);
 	free(orig_cwd);
 	for (i = 0; i < ARRAY_SIZE(env_names); i++) {
-		if (orig_env[i])
+		if (external_alias &&
+		    !strcmp(env_names[i], GIT_PREFIX_ENVIRONMENT))
+			continue;
+		if (orig_env[i]) {
 			setenv(env_names[i], orig_env[i], 1);
-		else
+			free(orig_env[i]);
+		} else {
 			unsetenv(env_names[i]);
+		}
 	}
 }
 
 static void commit_pager_choice(void) {
 	switch (use_pager) {
 	case 0:
