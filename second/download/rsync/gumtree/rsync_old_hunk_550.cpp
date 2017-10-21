	} else {
		if (!push_dir(lp_path(i), 0)) {
			rprintf(FERROR,"chdir %s failed\n", lp_path(i));
			io_printf(fd,"@ERROR: chdir failed\n");
			return -1;
		}
	}

	if (am_root) {
		if (setgid(gid)) {
			rprintf(FERROR,"setgid %d failed\n", gid);
			io_printf(fd,"@ERROR: setgid failed\n");
