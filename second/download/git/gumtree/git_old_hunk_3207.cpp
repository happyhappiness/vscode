	argc = parse_options(argc, argv, NULL, options, usage, 0);
	socket_path = argv[0];

	if (!socket_path)
		usage_with_options(usage, options);

	check_socket_directory(socket_path);
	register_tempfile(&socket_file, socket_path);

	if (ignore_sighup)
		signal(SIGHUP, SIG_IGN);

	serve_cache(socket_path, debug);
