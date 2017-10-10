 {
 	if (argc != 2)
 		die("submodule--helper is-active takes exactly 1 argument");
 
 	gitmodules_config();
 
-	return !is_submodule_initialized(argv[1]);
+	return !is_submodule_active(the_repository, argv[1]);
 }
 
 #define SUPPORT_SUPER_PREFIX (1<<0)
 
 struct cmd_struct {
 	const char *cmd;
