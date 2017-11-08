static int rsync_module(int fd, int i)
{
	int argc=0;
	char *argv[MAX_ARGS];
	char **argp;
	char line[1024];
	uid_t uid;
	gid_t gid;
	char *p;
	char *addr = client_addr(fd);
	char *host = client_name(fd);
	char *auth;
	char *name = lp_name(i);
	int start_glob=0;

	if (!allow_access(addr, host, lp_hosts_allow(i), lp_hosts_deny(i))) {
		rprintf(FERROR,"rsync denied on module %s from %s (%s)\n",
			name, client_name(fd), client_addr(fd));
		io_printf(fd,"@ERROR: access denied to %s from %s (%s)\n",
			  name, client_name(fd), client_addr(fd));
		return -1;
	}

	if (!auth_server(fd, i, addr, "@RSYNCD: AUTHREQD ")) {
		rprintf(FERROR,"auth failed on module %s from %s (%s)\n",
			name, client_name(fd), client_addr(fd));
		io_printf(fd,"@ERROR: auth failed on module %s\n",name);
		return -1;		
	}

	if (!claim_connection(lp_lock_file(), lp_max_connections())) {
		rprintf(FERROR,"max connections (%d) reached\n",
			lp_max_connections());
		io_printf(fd,"@ERROR: max connections (%d) reached - try again later\n", lp_max_connections());
		return -1;
	}

	rprintf(FINFO,"rsync on module %s from %s (%s)\n",
		name, host, addr);
	
	module_id = i;

	if (lp_read_only(i))
		read_only = 1;

	p = lp_uid(i);
	if (!name_to_uid(p, &uid)) {
		if (!isdigit(*p)) {
			rprintf(FERROR,"Invalid uid %s\n", p);
			io_printf(fd,"@ERROR: invalid uid\n");
			return -1;
		} 
		uid = atoi(p);
	}

	p = lp_gid(i);
	if (!name_to_gid(p, &gid)) {
		if (!isdigit(*p)) {
			rprintf(FERROR,"Invalid gid %s\n", p);
			io_printf(fd,"@ERROR: invalid gid\n");
			return -1;
		} 
		gid = atoi(p);
	}

	p = lp_exclude_from(i);
	add_exclude_file(p, 1);

	p = lp_exclude(i);
	add_exclude_line(p);

	if (chroot(lp_path(i))) {
		io_printf(fd,"@ERROR: chroot failed\n");
		return -1;
	}

	if (chdir("/")) {
		io_printf(fd,"@ERROR: chdir failed\n");
		return -1;
	}

	if (setgid(gid)) {
		io_printf(fd,"@ERROR: setgid failed\n");
		return -1;
	}

	if (setuid(uid)) {
		io_printf(fd,"@ERROR: setuid failed\n");
		return -1;
	}

	io_printf(fd,"@RSYNCD: OK\n");

	argv[argc++] = "rsyncd";

	while (1) {
		if (!read_line(fd, line, sizeof(line)-1)) {
			return -1;
		}

		if (!*line) break;

		p = line;

		if (start_glob && strncmp(p, name, strlen(name)) == 0) {
			p += strlen(name);
			if (!*p) p = ".";
		}

		argv[argc] = strdup(p);
		if (!argv[argc]) {
			return -1;
		}

		if (start_glob) {
			glob_expand(argv, &argc, MAX_ARGS);
		} else {
			argc++;
		}

		if (strcmp(line,".") == 0) {
			start_glob = 1;
		}

		if (argc == MAX_ARGS) {
			return -1;
		}
	}

	parse_arguments(argc, argv);

	/* don't allow the logs to be flooded too fast */
	if (verbose > 1) verbose = 1;

	argc -= optind;
	argp = argv + optind;
	optind = 0;

	start_server(fd, fd, argc, argp);

	return 0;
}