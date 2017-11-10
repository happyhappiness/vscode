int cmd_main(int argc, const char **argv)
{
	int listen_port = 0;
	struct string_list listen_addr = STRING_LIST_INIT_NODUP;
	int serve_mode = 0, inetd_mode = 0;
	const char *pid_file = NULL, *user_name = NULL, *group_name = NULL;
	int detach = 0;
	struct credentials *cred = NULL;
	int i;

	for (i = 1; i < argc; i++) {
		const char *arg = argv[i];
		const char *v;

		if (skip_prefix(arg, "--listen=", &v)) {
			string_list_append(&listen_addr, xstrdup_tolower(v));
			continue;
		}
		if (skip_prefix(arg, "--port=", &v)) {
			char *end;
			unsigned long n;
			n = strtoul(v, &end, 0);
			if (*v && !*end) {
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
		if (skip_prefix(arg, "--access-hook=", &v)) {
			access_hook = v;
			continue;
		}
		if (skip_prefix(arg, "--timeout=", &v)) {
			timeout = atoi(v);
			continue;
		}
		if (skip_prefix(arg, "--init-timeout=", &v)) {
			init_timeout = atoi(v);
			continue;
		}
		if (skip_prefix(arg, "--max-connections=", &v)) {
			max_connections = atoi(v);
			if (max_connections < 0)
				max_connections = 0;	        /* unlimited */
			continue;
		}
		if (!strcmp(arg, "--strict-paths")) {
			strict_paths = 1;
			continue;
		}
		if (skip_prefix(arg, "--base-path=", &v)) {
			base_path = v;
			continue;
		}
		if (!strcmp(arg, "--base-path-relaxed")) {
			base_path_relaxed = 1;
			continue;
		}
		if (skip_prefix(arg, "--interpolated-path=", &v)) {
			interpolated_path = v;
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
		if (skip_prefix(arg, "--user-path=", &v)) {
			user_path = v;
			continue;
		}
		if (skip_prefix(arg, "--pid-file=", &v)) {
			pid_file = v;
			continue;
		}
		if (!strcmp(arg, "--detach")) {
			detach = 1;
			log_syslog = 1;
			continue;
		}
		if (skip_prefix(arg, "--user=", &v)) {
			user_name = v;
			continue;
		}
		if (skip_prefix(arg, "--group=", &v)) {
			group_name = v;
			continue;
		}
		if (skip_prefix(arg, "--enable=", &v)) {
			enable_service(v, 1);
			continue;
		}
		if (skip_prefix(arg, "--disable=", &v)) {
			enable_service(v, 0);
			continue;
		}
		if (skip_prefix(arg, "--allow-override=", &v)) {
			make_service_overridable(v, 1);
			continue;
		}
		if (skip_prefix(arg, "--forbid-override=", &v)) {
			make_service_overridable(v, 0);
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