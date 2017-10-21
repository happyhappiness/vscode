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
