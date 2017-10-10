 		if (daemonize())
 			die("--detach not supported on this platform");
 	} else
 		sanitize_stdfds();
 
 	if (pid_file)
-		store_pid(pid_file);
+		write_file(pid_file, 1, "%"PRIuMAX"\n", (uintmax_t) getpid());
 
 	/* prepare argv for serving-processes */
 	cld_argv = xmalloc(sizeof (char *) * (argc + 2));
 	cld_argv[0] = argv[0];	/* git-daemon */
 	cld_argv[1] = "--serve";
 	for (i = 1; i < argc; ++i)
