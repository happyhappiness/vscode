	int start_glob=0;
	int ret;
	char *request=NULL;
	extern int am_sender;
	extern int am_server;
	extern int am_daemon;
	extern int am_root;

	if (!allow_access(addr, host, lp_hosts_allow(i), lp_hosts_deny(i))) {
		rprintf(FERROR,"rsync denied on module %s from %s (%s)\n",
			name, host, addr);
		io_printf(f_out, "@ERROR: access denied to %s from %s (%s)\n",
