 			(*argv)++;
 			(*argc)--;
 		} else if (skip_prefix(cmd, "--work-tree=", &cmd)) {
 			setenv(GIT_WORK_TREE_ENVIRONMENT, cmd, 1);
 			if (envchanged)
 				*envchanged = 1;
+		} else if (!strcmp(cmd, "--super-prefix")) {
+			if (*argc < 2) {
+				fprintf(stderr, "No prefix given for --super-prefix.\n" );
+				usage(git_usage_string);
+			}
+			setenv(GIT_SUPER_PREFIX_ENVIRONMENT, (*argv)[1], 1);
+			if (envchanged)
+				*envchanged = 1;
+			(*argv)++;
+			(*argc)--;
+		} else if (skip_prefix(cmd, "--super-prefix=", &cmd)) {
+			setenv(GIT_SUPER_PREFIX_ENVIRONMENT, cmd, 1);
+			if (envchanged)
+				*envchanged = 1;
 		} else if (!strcmp(cmd, "--bare")) {
 			char *cwd = xgetcwd();
 			is_bare_repository_cfg = 1;
 			setenv(GIT_DIR_ENVIRONMENT, cwd, 0);
 			free(cwd);
 			setenv(GIT_IMPLICIT_WORK_TREE_ENVIRONMENT, "0", 1);
