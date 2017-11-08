static int start_client(int argc, char *argv[])
{
	char *p;
	char *shell_machine = NULL;
	char *shell_path = NULL;
	char *shell_user = NULL;
	int ret;
	pid_t pid;
	int f_in,f_out;
	extern int local_server;
	extern int am_sender;
	extern char *shell_cmd;
	extern int rsync_port;
	extern int whole_file;
	extern int write_batch;
	extern int read_batch;
	int rc;

	/* Don't clobber argv[] so that ps(1) can still show the right
           command line. */
	if ((rc = copy_argv (argv)))
		return rc;

	if (strncasecmp(URL_PREFIX, argv[0], strlen(URL_PREFIX)) == 0) {
		char *host, *path;

		host = argv[0] + strlen(URL_PREFIX);
		p = strchr(host,'/');
		if (p) {
			*p = 0;
			path = p+1;
		} else {
			path="";
		}
		p = strchr(host,':');
		if (p) {
			rsync_port = atoi(p+1);
			*p = 0;
		}
		return start_socket_client(host, path, argc-1, argv+1);
	}

	if (!read_batch) {
	    p = find_colon(argv[0]);

	if (p) {
		if (p[1] == ':') { /* double colon */
			*p = 0;
			return start_socket_client(argv[0], p+2, argc-1, argv+1);
		}

		if (argc < 1) {
			usage(FERROR);
			exit_cleanup(RERR_SYNTAX);
		}

		am_sender = 0;
		*p = 0;
		shell_machine = argv[0];
		shell_path = p+1;
		argc--;
		argv++;
	} else {
		am_sender = 1;

		p = find_colon(argv[argc-1]);
		if (!p) {
			local_server = 1;
		} else if (p[1] == ':') {
			*p = 0;
			return start_socket_client(argv[argc-1], p+2, argc-1, argv);
		}

		if (argc < 2) {
			usage(FERROR);
			exit_cleanup(RERR_SYNTAX);
		}
		
		if (local_server) {
			shell_machine = NULL;
			shell_path = argv[argc-1];
		} else {
			*p = 0;
			shell_machine = argv[argc-1];
			shell_path = p+1;
		}
		argc--;
	}
	} else {
	    am_sender = 1;
	    local_server = 1;
	    shell_path = argv[argc-1];
	}

	if (shell_machine) {
		p = strchr(shell_machine,'@');
		if (p) {
			*p = 0;
			shell_user = shell_machine;
			shell_machine = p+1;
		}
	}

	if (verbose > 3) {
		rprintf(FINFO,"cmd=%s machine=%s user=%s path=%s\n",
			shell_cmd?shell_cmd:"",
			shell_machine?shell_machine:"",
			shell_user?shell_user:"",
			shell_path?shell_path:"");
	}
	
	if (!am_sender && argc > 1) {
		usage(FERROR);
		exit_cleanup(RERR_SYNTAX);
	}

	if (argc == 0 && !am_sender) {
		extern int list_only;
		list_only = 1;
	}
	
	pid = do_cmd(shell_cmd,shell_machine,shell_user,shell_path,&f_in,&f_out);
	
	ret = client_run(f_in, f_out, pid, argc, argv);

	fflush(stdout);
	fflush(stderr);

	return ret;
}