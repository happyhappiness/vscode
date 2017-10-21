
	for (i=0;i<sargc;i++) {
		io_printf(fd,"%s\n", sargs[i]);
	}
	io_printf(fd,"\n");

	if (remote_version < 23) {
		if (remote_version == 22 || (remote_version > 17 && !am_sender))
			io_start_multiplex_in(fd);
	}

	return client_run(fd, fd, -1, argc, argv);
}



