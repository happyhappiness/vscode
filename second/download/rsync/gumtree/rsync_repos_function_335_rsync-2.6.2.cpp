static pid_t do_cmd(char *cmd, char *machine, char *user, char *path,
		    int *f_in, int *f_out)
{
	int i, argc = 0;
	char *args[100];
	pid_t ret;
	char *tok, *dir = NULL;
	int dash_l_set = 0;

	if (!read_batch && !local_server) {
		char *rsh_env = getenv(RSYNC_RSH_ENV);
		if (!cmd)
			cmd = rsh_env;
		if (!cmd)
			cmd = RSYNC_RSH;
		cmd = strdup(cmd);
		if (!cmd)
			goto oom;

		for (tok = strtok(cmd, " "); tok; tok = strtok(NULL, " "))
			args[argc++] = tok;

		/* check to see if we've already been given '-l user' in
		 * the remote-shell command */
		for (i = 0; i < argc-1; i++) {
			if (!strcmp(args[i], "-l") && args[i+1][0] != '-')
				dash_l_set = 1;
		}

#if HAVE_REMSH
		/* remsh (on HPUX) takes the arguments the other way around */
		args[argc++] = machine;
		if (user && !(daemon_over_rsh && dash_l_set)) {
			args[argc++] = "-l";
			args[argc++] = user;
		}
#else
		if (user && !(daemon_over_rsh && dash_l_set)) {
			args[argc++] = "-l";
			args[argc++] = user;
		}
		args[argc++] = machine;
#endif

		args[argc++] = rsync_path;

		if (blocking_io < 0) {
			char *cp;
			if ((cp = strrchr(cmd, '/')) != NULL)
				cp++;
			else
				cp = cmd;
			if (strcmp(cp, "rsh") == 0 || strcmp(cp, "remsh") == 0)
				blocking_io = 1;
		}

		server_options(args,&argc);
	}

	args[argc++] = ".";

	if (!daemon_over_rsh && path && *path)
		args[argc++] = path;

	if (argc >= (int)(sizeof args / sizeof args[0])) {
		rprintf(FERROR, "internal: args[] overflowed in do_cmd()\n");
		exit_cleanup(RERR_MALLOC); /* XXX Need better RERR? */
	}

	args[argc] = NULL;

	if (verbose > 3) {
		rprintf(FINFO,"cmd=");
		for (i=0;i<argc;i++)
			rprintf(FINFO,"%s ",args[i]);
		rprintf(FINFO,"\n");
	}

	if (local_server) {
		if (read_batch)
			create_flist_from_batch(); /* sets batch_flist */
		ret = local_child(argc, args, f_in, f_out, child_main);
	} else {
		ret = piped_child(args,f_in,f_out);
	}

	if (dir) free(dir);

	return ret;

oom:
	out_of_memory("do_cmd");
	return 0; /* not reached */
}