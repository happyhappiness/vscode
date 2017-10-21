 			if (!(argv = realloc_array(argv, char *, maxargs)))
 				out_of_memory("rsync_module");
 		}
 		if (!(argv[argc] = strdup(p)))
 			out_of_memory("rsync_module");
 
-		if (start_glob) {
-			if (start_glob == 1) {
-				request = strdup(p);
-				start_glob++;
-			}
-			glob_expand(name, &argv, &argc, &maxargs);
-		} else
+		switch (start_glob) {
+		case 0:
 			argc++;
+			if (strcmp(line, ".") == 0)
+				start_glob = 1;
+			break;
+		case 1:
+			if (pre_exec_pid) {
+				err_msg = finish_pre_exec(pre_exec_pid,
+							  pre_exec_fd, p,
+							  argc, argv);
+				pre_exec_pid = 0;
+			}
+			request = strdup(p);
+			start_glob = 2;
+			/* FALL THROUGH */
+		default:
+			if (!err_msg)
+				glob_expand(name, &argv, &argc, &maxargs);
+			break;
+		}
+	}
 
-		if (strcmp(line, ".") == 0)
-			start_glob = 1;
+	if (pre_exec_pid) {
+		err_msg = finish_pre_exec(pre_exec_pid, pre_exec_fd, request,
+					  argc, argv);
 	}
 
 	verbose = 0; /* future verbosity is controlled by client options */
-	argp = argv;
-	ret = parse_arguments(&argc, (const char ***) &argp, 0);
+	ret = parse_arguments(&argc, (const char ***) &argv, 0);
+	quiet = 0; /* Don't let someone try to be tricky. */
 
 	if (filesfrom_fd == 0)
 		filesfrom_fd = f_in;
 
 	if (request) {
 		if (*auth_user) {
