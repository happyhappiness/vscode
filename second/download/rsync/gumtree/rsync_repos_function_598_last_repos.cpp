int main(int argc,char *argv[])
{
	int ret;
	int orig_argc = argc;
	char **orig_argv = argv;
#ifdef HAVE_SIGACTION
# ifdef HAVE_SIGPROCMASK
	sigset_t sigmask;

	sigemptyset(&sigmask);
# endif
	sigact.sa_flags = SA_NOCLDSTOP;
#endif
	SIGACTMASK(SIGUSR1, sigusr1_handler);
	SIGACTMASK(SIGUSR2, sigusr2_handler);
	SIGACTMASK(SIGCHLD, remember_children);
#ifdef MAINTAINER_MODE
	SIGACTMASK(SIGSEGV, rsync_panic_handler);
	SIGACTMASK(SIGFPE, rsync_panic_handler);
	SIGACTMASK(SIGABRT, rsync_panic_handler);
	SIGACTMASK(SIGBUS, rsync_panic_handler);
#endif

	starttime = time(NULL);
	our_uid = MY_UID();
	our_gid = MY_GID();
	am_root = our_uid == 0;

	memset(&stats, 0, sizeof(stats));

	if (argc < 2) {
		usage(FERROR);
		exit_cleanup(RERR_SYNTAX);
	}

	/* Get the umask for use in permission calculations.  We no longer set
	 * it to zero; that is ugly and pointless now that all the callers that
	 * relied on it have been reeducated to work with default ACLs. */
	umask(orig_umask = umask(0));

#if defined CONFIG_LOCALE && defined HAVE_SETLOCALE
	setlocale(LC_CTYPE, "");
#endif

	if (!parse_arguments(&argc, (const char ***) &argv)) {
		/* FIXME: We ought to call the same error-handling
		 * code here, rather than relying on getopt. */
		option_error();
		exit_cleanup(RERR_SYNTAX);
	}

	SIGACTMASK(SIGINT, sig_int);
	SIGACTMASK(SIGHUP, sig_int);
	SIGACTMASK(SIGTERM, sig_int);
#if defined HAVE_SIGACTION && HAVE_SIGPROCMASK
	sigprocmask(SIG_UNBLOCK, &sigmask, NULL);
#endif

	/* Ignore SIGPIPE; we consistently check error codes and will
	 * see the EPIPE. */
	SIGACTION(SIGPIPE, SIG_IGN);
#ifdef SIGXFSZ
	SIGACTION(SIGXFSZ, SIG_IGN);
#endif

	/* Initialize change_dir() here because on some old systems getcwd
	 * (implemented by forking "pwd" and reading its output) doesn't
	 * work when there are other child processes.  Also, on all systems
	 * that implement getcwd that way "pwd" can't be found after chroot. */
	change_dir(NULL, CD_NORMAL);

	init_flist();

	if ((write_batch || read_batch) && !am_server) {
		if (write_batch)
			write_batch_shell_file(orig_argc, orig_argv, argc);

		if (read_batch && strcmp(batch_name, "-") == 0)
			batch_fd = STDIN_FILENO;
		else {
			batch_fd = do_open(batch_name,
				   write_batch ? O_WRONLY | O_CREAT | O_TRUNC
				   : O_RDONLY, S_IRUSR | S_IWUSR);
		}
		if (batch_fd < 0) {
			rsyserr(FERROR, errno, "Batch file %s open error",
				full_fname(batch_name));
			exit_cleanup(RERR_FILEIO);
		}
		if (read_batch)
			read_stream_flags(batch_fd);
		else
			write_stream_flags(batch_fd);
	}
	if (write_batch < 0)
		dry_run = 1;

	if (am_server) {
#ifdef ICONV_CONST
		setup_iconv();
#endif
	} else if (am_daemon)
		return daemon_main();

	if (am_server && protect_args) {
		char buf[MAXPATHLEN];
		protect_args = 2;
		read_args(STDIN_FILENO, NULL, buf, sizeof buf, 1, &argv, &argc, NULL);
		if (!parse_arguments(&argc, (const char ***) &argv)) {
			option_error();
			exit_cleanup(RERR_SYNTAX);
		}
	}

	if (argc < 1) {
		usage(FERROR);
		exit_cleanup(RERR_SYNTAX);
	}

	if (am_server) {
		set_nonblocking(STDIN_FILENO);
		set_nonblocking(STDOUT_FILENO);
		if (am_daemon)
			return start_daemon(STDIN_FILENO, STDOUT_FILENO);
		start_server(STDIN_FILENO, STDOUT_FILENO, argc, argv);
	}

	ret = start_client(argc, argv);
	if (ret == -1)
		exit_cleanup(RERR_STARTCLIENT);
	else
		exit_cleanup(ret);

	return ret;
}