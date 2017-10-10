 	argc = parse_options(argc, argv, NULL, options, usage, 0);
 	if (!argc)
 		usage_with_options(usage, options);
 	op = argv[0];
 
 	if (!socket_path)
-		socket_path = expand_user_path("~/.git-credential-cache/socket");
+		socket_path = get_socket_path();
 	if (!socket_path)
 		die("unable to find a suitable socket path; use --socket");
 
 	if (!strcmp(op, "exit"))
 		do_cache(socket_path, op, timeout, 0);
 	else if (!strcmp(op, "get") || !strcmp(op, "erase"))
