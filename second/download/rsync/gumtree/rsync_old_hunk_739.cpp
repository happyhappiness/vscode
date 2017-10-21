			io_printf(f_out, "@ERROR: max connections (%d) reached - try again later\n",
				lp_max_connections(i));
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

	am_root = (MY_UID() == 0);

	if (am_root) {
		p = lp_uid(i);
		if (!name_to_uid(p, &uid)) {
			if (!isdigit(* (unsigned char *) p)) {
				rprintf(FERROR,"Invalid uid %s\n", p);
				io_printf(f_out, "@ERROR: invalid uid %s\n", p);
				return -1;
			}
			uid = atoi(p);
		}

		p = lp_gid(i);
		if (!name_to_gid(p, &gid)) {
			if (!isdigit(* (unsigned char *) p)) {
				rprintf(FERROR,"Invalid gid %s\n", p);
				io_printf(f_out, "@ERROR: invalid gid %s\n", p);
				return -1;
			}
			gid = atoi(p);
		}
	}
