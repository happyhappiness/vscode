 	 * environment, and the $(gitexecdir) from the Makefile at build
 	 * time.
 	 */
 	setup_path();
 
 	while (1) {
-		static int done_help = 0;
-		static int was_alias = 0;
-		was_alias = run_argv(&argc, &argv);
+		int was_alias = run_argv(&argc, &argv);
 		if (errno != ENOENT)
 			break;
 		if (was_alias) {
 			fprintf(stderr, "Expansion of alias '%s' failed; "
 				"'%s' is not a git command\n",
 				cmd, argv[0]);
