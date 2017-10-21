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

	
	auth_user = auth_server(fd, i, addr, "@RSYNCD: AUTHREQD ");
