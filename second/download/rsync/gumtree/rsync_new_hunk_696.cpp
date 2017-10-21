	for (i = 0; i < sargc; i++) {
		io_printf(f_out, "%s\n", sargs[i]);
	}
	io_printf(f_out, "\n");

	if (protocol_version < 23) {
		if (protocol_version == 22 || !am_sender)
			io_start_multiplex_in(f_in);
	}

	return 0;
}

