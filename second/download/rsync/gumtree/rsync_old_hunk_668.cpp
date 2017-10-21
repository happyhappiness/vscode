
	for (i = 0; i < sargc; i++) {
		io_printf(f_out, "%s\n", sargs[i]);
	}
	io_printf(f_out, "\n");

	if (remote_version < 23) {
		if (remote_version == 22 || (remote_version > 17 && !am_sender))
			io_start_multiplex_in(f_in);
	}

	return 0;
}

