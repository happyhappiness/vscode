int main(int argc,char *argv[])
{       
	extern int am_root;
	extern int orig_umask;
	extern int dry_run;
	extern int am_daemon;
	extern int am_server;
	int ret;
	extern int write_batch;
	int orig_argc;
	char **orig_argv;

	orig_argc = argc;
	orig_argv = argv;

	signal(SIGUSR1, sigusr1_handler);
	signal(SIGUSR2, sigusr2_handler);
	signal(SIGCHLD, sigchld_handler);
#ifdef MAINTAINER_MODE
	signal(SIGSEGV, rsync_panic_handler);
	signal(SIGFPE, rsync_panic_handler);
	signal(SIGABRT, rsync_panic_handler);
	signal(SIGBUS, rsync_panic_handler);
#endif /* def MAINTAINER_MODE */

	starttime = time(NULL);
	am_root = (getuid() == 0);

	memset(&stats, 0, sizeof(stats));

	if (argc < 2) {
		usage(FERROR);
		exit_cleanup(RERR_SYNTAX);
	}

	/* we set a 0 umask so that correct file permissions can be
	   carried across */
	orig_umask = (int)umask(0);

	if (!parse_arguments(&argc, (const char ***) &argv, 1)) {
                /* FIXME: We ought to call the same error-handling
                 * code here, rather than relying on getopt. */
		option_error();
		exit_cleanup(RERR_SYNTAX);
	}

	signal(SIGINT,SIGNAL_CAST sig_int);
	signal(SIGHUP,SIGNAL_CAST sig_int);
	signal(SIGTERM,SIGNAL_CAST sig_int);

	/* Ignore SIGPIPE; we consistently check error codes and will
	 * see the EPIPE. */
	signal(SIGPIPE, SIG_IGN);

	/* Initialize push_dir here because on some old systems getcwd
	   (implemented by forking "pwd" and reading its output) doesn't
	   work when there are other child processes.  Also, on all systems
	   that implement getcwd that way "pwd" can't be found after chroot. */
	push_dir(NULL,0);

	if (write_batch && !am_server) {
	    write_batch_argvs_file(orig_argc, orig_argv);
	}

	if (am_daemon) {
		return daemon_main();
	}

	if (argc < 1) {
		usage(FERROR);
		exit_cleanup(RERR_SYNTAX);
	}

	if (dry_run)
		verbose = MAX(verbose,1);

#ifndef SUPPORT_LINKS
	if (!am_server && preserve_links) {
		rprintf(FERROR,"ERROR: symbolic links not supported\n");
		exit_cleanup(RERR_UNSUPPORTED);
	}
#endif

	if (am_server) {
		set_nonblocking(STDIN_FILENO);
		set_nonblocking(STDOUT_FILENO);
		start_server(STDIN_FILENO, STDOUT_FILENO, argc, argv);
	}

	ret = start_client(argc, argv);
	if (ret == -1) 
		exit_cleanup(RERR_STARTCLIENT);
	else
		exit_cleanup(ret);

	exit(ret);
	/* NOTREACHED */
}