 		absorb_git_dir_into_superproject(prefix,
 				list.entries[i]->name, flags);
 
 	return 0;
 }
 
+static int is_active(int argc, const char **argv, const char *prefix)
+{
+	if (argc != 2)
+		die("submodule--helper is-active takes exactly 1 argument");
+
+	gitmodules_config();
+
+	return !is_submodule_initialized(argv[1]);
+}
+
 #define SUPPORT_SUPER_PREFIX (1<<0)
 
 struct cmd_struct {
 	const char *cmd;
 	int (*fn)(int, const char **, const char *);
 	unsigned option;
