
	for (i=0;i<sargc;i++) {
		io_printf(fd,"%s\n", sargs[i]);
	}
	io_printf(fd,"\n");

	return client_run(fd, fd, -1, argc, argv);
}



static int rsync_module(int fd, int i)
