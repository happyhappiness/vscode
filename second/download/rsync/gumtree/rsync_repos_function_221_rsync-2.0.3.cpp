int start_client(int argc, char *argv[])
{
	char *p;
	char *shell_machine = NULL;
	char *shell_path = NULL;
	char *shell_user = NULL;
	int pid;
	int f_in,f_out;
	extern int local_server;
	extern int am_sender;
	extern char *shell_cmd;

	p = strchr(argv[0],':');

	if (p) {
		if (p[1] == ':') {
			*p = 0;
			return start_socket_client(argv[0], p+2, argc-1, argv+1);
		}

		if (argc < 2) {
			usage(FERROR);
			exit_cleanup(1);
		}

		am_sender = 0;
		*p = 0;
		shell_machine = argv[0];
		shell_path = p+1;
		argc--;
		argv++;
	} else {
		am_sender = 1;

		p = strchr(argv[argc-1],':');
		if (!p) {
			local_server = 1;
		} else if (p[1] == ':') {
			*p = 0;
			return start_socket_client(argv[argc-1], p+2, argc-1, argv);
		}

		if (argc < 2) {
			usage(FERROR);
			exit_cleanup(1);
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
	
	if (!am_sender && argc != 1) {
		usage(FERROR);
		exit_cleanup(1);
	}
	
	pid = do_cmd(shell_cmd,shell_machine,shell_user,shell_path,&f_in,&f_out);
	
#if HAVE_SETLINEBUF
	setlinebuf(stdout);
	setlinebuf(stderr);
#endif

	return client_run(f_in, f_out, pid, argc, argv);
}