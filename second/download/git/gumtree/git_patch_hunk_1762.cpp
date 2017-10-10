 				}
 				putchar('\n');
 				continue;
 			}
 			if (!strcmp(arg, "--git-dir")) {
 				const char *gitdir = getenv(GIT_DIR_ENVIRONMENT);
-				static char cwd[PATH_MAX];
+				char *cwd;
 				int len;
 				if (gitdir) {
 					puts(gitdir);
 					continue;
 				}
 				if (!prefix) {
 					puts(".git");
 					continue;
 				}
-				if (!getcwd(cwd, PATH_MAX))
-					die_errno("unable to get current working directory");
+				cwd = xgetcwd();
 				len = strlen(cwd);
 				printf("%s%s.git\n", cwd, len && cwd[len-1] != '/' ? "/" : "");
+				free(cwd);
 				continue;
 			}
 			if (!strcmp(arg, "--resolve-git-dir")) {
 				const char *gitdir = argv[++i];
 				if (!gitdir)
 					die("--resolve-git-dir requires an argument");
