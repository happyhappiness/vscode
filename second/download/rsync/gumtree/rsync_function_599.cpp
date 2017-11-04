static int rsync_module(int fd, int i)
{
	int argc=0;
	char *argv[MAX_ARGS];
	char **argp;
	char line[MAXPATHLEN];
	uid_t uid = (uid_t)-2;
	gid_t gid = (gid_t)-2;
	char *p;
	char *addr = client_addr(fd);
	char *host = client_name(fd);
	char *name = lp_name(i);
	char *user;
	int start_glob=0;
	char *request=NULL;
	extern int am_sender;
	extern int remote_version;
	extern int am_root;

	if (!allow_access(addr, host, lp_hosts_allow(i), lp_hosts_deny(i))) {
		rprintf(FERROR,"rsync denied on module %s from %s (%s)\n",
			name, client_name(fd), client_addr(fd));
		io_printf(fd,"@ERROR: access denied to %s from %s (%s)\n",
			  name, client_name(fd), client_addr(fd));
		return -1;
	}

	if (!claim_connection(lp_lock_file(), lp_max_connections())) {
		if (errno) {
			rprintf(FERROR,"failed to open lock file %s : %s\n",
				lp_lock_file(), strerror(errno));
			io_printf(fd,"@ERROR: failed to open lock file %s : %s\n",
				  lp_lock_file(), strerror(errno));
		} else {
			rprintf(FERROR,"max connections (%d) reached\n",
				lp_max_connections());
			io_printf(fd,"@ERROR: max connections (%d) reached - try again later\n", lp_max_connections());
		}
		return -1;
	}

	
	user = auth_server(fd, i, addr, "@RSYNCD: AUTHREQD ");

	if (!user) {
		rprintf(FERROR,"auth failed on module %s from %s (%s)\n",
			name, client_name(fd), client_addr(fd));
		io_printf(fd,"@ERROR: auth failed on module %s\n",name);
		return -1;		
	}

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
	add_exclude_file(p, 1, 0);

	p = lp_exclude(i);
	add_exclude_line(p);

	log_open();

	if (chroot(lp_path(i))) {
		rprintf(FERROR,"chroot %s failed\n", lp_path(i));
		io_printf(fd,"@ERROR: chroot failed\n");
		return -1;
	}

	if (chdir("/")) {
		rprintf(FERROR,"chdir %s failed\n", lp_path(i));
		io_printf(fd,"@ERROR: chdir failed\n");
		return -1;
	}

	if (setgid(gid) || getgid() != gid) {
		rprintf(FERROR,"setgid %d failed\n", gid);
		io_printf(fd,"@ERROR: setgid failed\n");
		return -1;
	}

	if (setuid(uid) || getuid() != uid) {
		rprintf(FERROR,"setuid %d failed\n", uid);
		io_printf(fd,"@ERROR: setuid failed\n");
		return -1;
	}

	am_root = (getuid() == 0);

	io_printf(fd,"@RSYNCD: OK\n");

	argv[argc++] = "rsyncd";

	while (1) {
		if (!read_line(fd, line, sizeof(line)-1)) {
			return -1;
		}

		if (!*line) break;

		p = line;

		argv[argc] = strdup(p);
		if (!argv[argc]) {
			return -1;
		}

		if (start_glob) {
			if (start_glob == 1) {
				request = strdup(p);
				start_glob++;
			}
			glob_expand(name, argv, &argc, MAX_ARGS);
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

	if (request) {
		if (*user) {
			rprintf(FINFO,"rsync %s %s from %s@%s (%s)\n",
				am_sender?"on":"to",
				request, user, host, addr);
		} else {
			rprintf(FINFO,"rsync %s %s from %s (%s)\n",
				am_sender?"on":"to",
				request, host, addr);
		}
		free(request);
	}

	/* don't allow the logs to be flooded too fast */
	if (verbose > 1) verbose = 1;

	argc -= optind;
	argp = argv + optind;
	optind = 0;

	if (remote_version > 17 && am_sender)
		io_start_multiplex_out(fd);

	start_server(fd, fd, argc, argp);

	return 0;
}