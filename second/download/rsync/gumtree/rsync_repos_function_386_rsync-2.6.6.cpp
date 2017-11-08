static int start_client(int argc, char *argv[])
{
	char *p;
	char *shell_machine = NULL;
	char *shell_path = NULL;
	char *shell_user = NULL;
	int ret;
	pid_t pid;
	int f_in,f_out;
	int rc;

	/* Don't clobber argv[] so that ps(1) can still show the right
	 * command line. */
	if ((rc = copy_argv(argv)))
		return rc;

	if (!read_batch) { /* for read_batch, NO source is specified */
		argc--;
		shell_path = check_for_hostspec(argv[0], &shell_machine, &rsync_port);
		if (shell_path) { /* source is remote */
			argv++;
			if (filesfrom_host && *filesfrom_host
			    && strcmp(filesfrom_host, shell_machine) != 0) {
				rprintf(FERROR,
					"--files-from hostname is not the same as the transfer hostname\n");
				exit_cleanup(RERR_SYNTAX);
			}
			if (rsync_port) {
				if (!shell_cmd) {
					return start_socket_client(shell_machine,
								   shell_path,
								   argc, argv);
				}
				daemon_over_rsh = 1;
			}

			am_sender = 0;
		} else { /* source is local, check dest arg */
			am_sender = 1;

			if (argc < 1) { /* destination required */
				usage(FERROR);
				exit_cleanup(RERR_SYNTAX);
			}

			shell_path = check_for_hostspec(argv[argc], &shell_machine, &rsync_port);
			if (shell_path && filesfrom_host && *filesfrom_host
			    && strcmp(filesfrom_host, shell_machine) != 0) {
				rprintf(FERROR,
					"--files-from hostname is not the same as the transfer hostname\n");
				exit_cleanup(RERR_SYNTAX);
			}
			if (!shell_path) { /* no hostspec found, so src & dest are local */
				local_server = 1;
				if (filesfrom_host) {
					rprintf(FERROR,
						"--files-from cannot be remote when the transfer is local\n");
					exit_cleanup(RERR_SYNTAX);
				}
				shell_machine = NULL;
				shell_path = argv[argc];
			} else if (rsync_port) {
				if (!shell_cmd) {
					return start_socket_client(shell_machine,
								   shell_path,
								   argc, argv);
				}
				daemon_over_rsh = 1;
			}
		}
	} else {  /* read_batch */
		local_server = 1;
		shell_path = argv[argc-1];
		if (check_for_hostspec(shell_path, &shell_machine, &rsync_port)) {
			rprintf(FERROR, "remote destination is not allowed with --read-batch\n");
			exit_cleanup(RERR_SYNTAX);
		}
	}

	if (shell_machine) {
		p = strrchr(shell_machine,'@');
		if (p) {
			*p = 0;
			shell_user = shell_machine;
			shell_machine = p+1;
		}
	}

	if (verbose > 3) {
		rprintf(FINFO,"cmd=%s machine=%s user=%s path=%s\n",
			shell_cmd ? safe_fname(shell_cmd) : "",
			shell_machine ? safe_fname(shell_machine) : "",
			shell_user ? safe_fname(shell_user) : "",
			shell_path ? safe_fname(shell_path) : "");
	}

	/* for remote source, only single dest arg can remain ... */
	if (!am_sender && argc > 1) {
		usage(FERROR);
		exit_cleanup(RERR_SYNTAX);
	}

	/* ... or no dest at all */
	if (!am_sender && argc == 0)
		list_only |= 1;

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