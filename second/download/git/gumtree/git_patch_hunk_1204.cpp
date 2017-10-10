 	my_argv[1] = arg;
 	my_argv[2] = NULL;
 
 	return execv_git_cmd(my_argv);
 }
 
-static int do_cvs_cmd(const char *me, char *arg)
-{
-	const char *cvsserver_argv[3] = {
-		"cvsserver", "server", NULL
-	};
-
-	if (!arg || strcmp(arg, "server"))
-		die("git-cvsserver only handles server: %s", arg);
-
-	setup_path();
-	return execv_git_cmd(cvsserver_argv);
-}
-
 static int is_valid_cmd_name(const char *cmd)
 {
 	/* Test command contains no . or / characters */
 	return cmd[strcspn(cmd, "./")] == '\0';
 }
 
