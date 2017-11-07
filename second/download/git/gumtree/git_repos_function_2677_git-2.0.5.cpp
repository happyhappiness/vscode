int main(int argc, char **argv)
{
	int listen_port = 0;
	struct string_list listen_addr = STRING_LIST_INIT_NODUP;
	int serve_mode = 0, inetd_mode = 0;
	const char *pid_file = NULL, *user_name = NULL, *group_name = NULL;
	int detach = 0;
	struct credentials *cred = NULL;
	int i;

	git_setup_gettext();

	git_extract_argv0_path(argv[0]);

	for (i = 1; i < argc; i++) {
		char *arg = argv[i];

		if (starts_with(arg, "--listen=")) {
			string_list_append(&listen_addr, xstrdup_tolower(arg + 9));
			continue;
		}
		if (starts_with(arg, "--port=")) {
			char *end;
			unsigned long n;
			n = strtoul(arg+7, &end, 0);
			if (arg[7] && !*end) {
				listen_port = n;
				continue;
			}
		}
		if (!strcmp(arg, "--serve")) {
			serve_mode = 1;
			continue;
		}
		if (!strcmp(arg, "--inetd")) {
			inetd_mode = 1;
			log_syslog = 1;
			continue;
		}
		if (!strcmp(arg, "--verbose")) {
			verbose = 1;
			continue;
		}
		if (!strcmp(arg, "--syslog")) {
			log_syslog = 1;
			continue;
		}
		if (!strcmp(arg, "--export-all")) {
			export_all_trees = 1;
			continue;
		}
		if (starts_with(arg, "--access-hook=")) {
			access_hook = arg + 14;
			continue;
		}
		if (starts_with(arg, "--timeout=")) {
			timeout = atoi(arg+10);
			continue;
		}
		if (starts_with(arg, "--init-timeout=")) {
			init_timeout = atoi(arg+15);
			continue;
		}
		if (starts_with(arg, "--max-connections=")) {
			max_connections = atoi(arg+18);
			if (max_connections < 0)
				max_connections = 0;	        /* unlimited */
			continue;
		}
		if (!strcmp(arg, "--strict-paths")) {
			strict_paths = 1;
			continue;
		}
		if (starts_with(arg, "--base-path=")) {
			base_path = arg+12;
			continue;
		}
		if (!strcmp(arg, "--base-path-relaxed")) {
			base_path_relaxed = 1;
			continue;
		}
		if (starts_with(arg, "--interpolated-path=")) {
			interpolated_path = arg+20;
			continue;
		}
		if (!strcmp(arg, "--reuseaddr")) {
			reuseaddr = 1;
			continue;
		}
		if (!strcmp(arg, "--user-path")) {
			user_path = "";
			continue;
		}
		if (starts_with(arg, "--user-path=")) {
			user_path = arg + 12;
			continue;
		}
		if (starts_with(arg, "--pid-file=")) {
			pid_file = arg + 11;
			continue;
		}
		if (!strcmp(arg, "--detach")) {
			detach = 1;
			log_syslog = 1;
			continue;
		}
		if (starts_with(arg, "--user=")) {
			user_name = arg + 7;
			continue;
		}
		if (starts_with(arg, "--group=")) {
			group_name = arg + 8;
			continue;
		}
		if (starts_with(arg, "--enable=")) {
			enable_service(arg + 9, 1);
			continue;
		}
		if (starts_with(arg, "--disable=")) {
			enable_service(arg + 10, 0);
			continue;
		}
		if (starts_with(arg, "--allow-override=")) {
			make_service_overridable(arg + 17, 1);
			continue;
		}
		if (starts_with(arg, "--forbid-override=")) {
			make_service_overridable(arg + 18, 0);
			continue;
		}
		if (!strcmp(arg, "--informative-errors")) {
			informative_errors = 1;
			continue;
		}
		if (!strcmp(arg, "--no-informative-errors")) {
			informative_errors = 0;
			continue;
		}
		if (!strcmp(arg, "--")) {
			ok_paths = &argv[i+1];
			break;
		} else if (arg[0] != '-') {
			ok_paths = &argv[i];
			break;
		}

		usage(daemon_usage);
	}

	if (log_syslog) {
		openlog("git-daemon", LOG_PID, LOG_DAEMON);
		set_die_routine(daemon_die);
	} else
		/* avoid splitting a message in the middle */
		setvbuf(stderr, NULL, _IOFBF, 4096);

	if (inetd_mode && (detach || group_name || user_name))
		die("--detach, --user and --group are incompatible with --inetd");

	if (inetd_mode && (listen_port || (listen_addr.nr > 0)))
		die("--listen= and --port= are incompatible with --inetd");
	else if (listen_port == 0)
		listen_port = DEFAULT_GIT_PORT;

	if (group_name && !user_name)
		die("--group supplied without --user");

	if (user_name)
		cred = prepare_credentials(user_name, group_name);

	if (strict_paths && (!ok_paths || !*ok_paths))
		die("option --strict-paths requires a whitelist");

	if (base_path && !is_directory(base_path))
		die("base-path '%s' does not exist or is not a directory",
		    base_path);

	if (inetd_mode) {
		if (!freopen("/dev/null", "w", stderr))
			die_errno("failed to redirect stderr to /dev/null");
	}

	if (inetd_mode || serve_mode)
		return execute();

	if (detach) {
		if (daemonize())
			die("--detach not supported on this platform");
	} else
		sanitize_stdfds();

	if (pid_file)
		store_pid(pid_file);

	/* prepare argv for serving-processes */
	cld_argv = xmalloc(sizeof (char *) * (argc + 2));
	cld_argv[0] = argv[0];	/* git-daemon */
	cld_argv[1] = "--serve";
	for (i = 1; i < argc; ++i)
		cld_argv[i+1] = argv[i];
	cld_argv[argc+1] = NULL;

	return serve(&listen_addr, listen_port, cred);
}