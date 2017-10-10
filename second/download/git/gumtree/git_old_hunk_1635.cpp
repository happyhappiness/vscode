
	while (1) {
		char in[1024];
		int r;

		r = read_in_full(fd, in, sizeof(in));
		if (r == 0)
			break;
		if (r < 0)
			die_errno("read error from cache daemon");
		write_or_die(1, in, r);
		got_data = 1;
	}
