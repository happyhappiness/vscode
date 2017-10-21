	uid_t uid = (uid_t)-2;
	gid_t gid = (gid_t)-2;
	char *p;
	char *addr = client_addr(fd);
	char *host = client_name(fd);
	char *name = lp_name(i);
	int start_glob=0;
	char *request=NULL;
	extern int am_sender;

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

	
	module_id = i;

	if (lp_read_only(i))
		read_only = 1;

	p = lp_uid(i);
