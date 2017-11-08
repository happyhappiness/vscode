int main(int argc,char *argv[])
{       
	extern int am_root;
	extern int orig_umask;
	extern int dry_run;
	extern int am_daemon;
	extern int am_server;

	signal(SIGUSR1, sigusr1_handler);

	starttime = time(NULL);
	am_root = (getuid() == 0);

	memset(&stats, 0, sizeof(stats));

	if (argc < 2) {
		usage(FERROR);
		exit_cleanup(1);
	}

	/* we set a 0 umask so that correct file permissions can be
	   carried across */
	orig_umask = (int)umask(0);

	parse_arguments(argc, argv);

	argc -= optind;
	argv += optind;
	optind = 0;

	signal(SIGCHLD,SIG_IGN);
	signal(SIGINT,SIGNAL_CAST sig_int);
	signal(SIGPIPE,SIGNAL_CAST sig_int);
	signal(SIGHUP,SIGNAL_CAST sig_int);

	if (am_daemon) {
		return daemon_main();
	}

	if (argc < 1) {
		usage(FERROR);
		exit_cleanup(1);
	}

	if (dry_run)
		verbose = MAX(verbose,1);

#ifndef SUPPORT_LINKS
	if (!am_server && preserve_links) {
		rprintf(FERROR,"ERROR: symbolic links not supported\n");
		exit_cleanup(1);
	}
#endif

	if (am_server) {
		start_server(STDIN_FILENO, STDOUT_FILENO, argc, argv);
	}

	return start_client(argc, argv);
}