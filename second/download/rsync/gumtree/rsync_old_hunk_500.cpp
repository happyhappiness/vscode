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

