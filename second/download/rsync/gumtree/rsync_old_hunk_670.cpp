				lp_lock_file(i), strerror(errno));
			io_printf(f_out, "@ERROR: failed to open lock file %s : %s\n",
				  lp_lock_file(i), strerror(errno));
		} else {
			rprintf(FERROR,"max connections (%d) reached\n",
				lp_max_connections(i));
			io_printf(f_out, "@ERROR: max connections (%d) reached - try again later\n", lp_max_connections(i));
		}
		return -1;
	}

	
	auth_user = auth_server(f_in, f_out, i, addr, "@RSYNCD: AUTHREQD ");

	if (!auth_user) {
		rprintf(FERROR,"auth failed on module %s from %s (%s)\n",
			name, host, addr);
		io_printf(f_out, "@ERROR: auth failed on module %s\n", name);
		return -1;		
	}

	module_id = i;

	am_root = (getuid() == 0);

