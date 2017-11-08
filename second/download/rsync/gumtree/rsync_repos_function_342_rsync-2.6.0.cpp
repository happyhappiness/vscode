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
	extern char *shell_cmd;
	extern int rsync_port;
	extern int daemon_over_rsh;
	extern int read_batch;
	int rc;

	/* Don't clobber argv[] so that ps(1) can still show the right
	 * command line. */
	if ((rc = copy_argv(argv)))
		return rc;

	/* rsync:// always uses rsync server over direct socket connection */
	if (strncasecmp(URL_PREFIX, argv[0], strlen(URL_PREFIX)) == 0) {
		char *host, *path;

		host = argv[0] + strlen(URL_PREFIX);
		p = strchr(host,'/');
		if (p) {
			*p = 0;
			path = p+1;
		} else {
			path = "";
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
			if (remote_filesfrom_file
			 && remote_filesfrom_file != files_from + 1
			 && strncmp(files_from, argv[0], p-argv[0]+1) != 0) {
				rprintf(FERROR,
					"--files-from hostname is not transfer hostname\n");
				exit_cleanup(RERR_SYNTAX);
			}
			if (p[1] == ':') { /* double colon */
				*p = 0;
				if (!shell_cmd) {
					return start_socket_client(argv[0], p+2,
								   argc-1, argv+1);
				}
				p++;
				daemon_over_rsh = 1;
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

			/* rsync:// destination uses rsync server over direct socket */
			if (strncasecmp(URL_PREFIX, argv[argc-1], strlen(URL_PREFIX)) == 0) {
				char *host, *path;

				host = argv[argc-1] + strlen(URL_PREFIX);
				p = strchr(host,'/');
				if (p) {
					*p = 0;
					path = p+1;
				} else {
					path = "";
				}
				p = strchr(host,':');
				if (p) {
					rsync_port = atoi(p+1);
					*p = 0;
				}
				return start_socket_client(host, path, argc-1, argv);
			}

			p = find_colon(argv[argc-1]);
			if (p && remote_filesfrom_file
			 && remote_filesfrom_file != files_from + 1
			 && strncmp(files_from, argv[argc-1], p-argv[argc-1]+1) != 0) {
				rprintf(FERROR,
					"--files-from hostname is not transfer hostname\n");
				exit_cleanup(RERR_SYNTAX);
			}
			if (!p) {
				local_server = 1;
				if (remote_filesfrom_file) {
					rprintf(FERROR,
						"--files-from is remote but transfer is local\n");
					exit_cleanup(RERR_SYNTAX);
				}
			} else if (p[1] == ':') { /* double colon */
				*p = 0;
				if (!shell_cmd) {
					return start_socket_client(argv[argc-1], p+2,
								   argc-1, argv);
				}
				p++;
				daemon_over_rsh = 1;
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

	pid = do_cmd(shell_cmd,shell_machine,shell_user,shell_path,
		     &f_in,&f_out);

	/* if we're running an rsync server on the remote host over a
	 * remote shell command, we need to do the RSYNCD protocol first */
	if (daemon_over_rsh) {
		int tmpret;
		tmpret = start_inband_exchange(shell_user, shell_path,
					       f_in, f_out, argc);
		if (tmpret < 0)
			return tmpret;
	}

	ret = client_run(f_in, f_out, pid, argc, argv);

	fflush(stdout);
	fflush(stderr);

	return ret;
}