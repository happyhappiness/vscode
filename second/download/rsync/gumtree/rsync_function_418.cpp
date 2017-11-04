static int do_cmd(char *cmd,char *machine,char *user,char *path,int *f_in,int *f_out)
{
	char *args[100];
	int i,argc=0, ret;
	char *tok,*dir=NULL;

	if (!local_server) {
		if (!cmd)
			cmd = getenv(RSYNC_RSH_ENV);
		if (!cmd)
			cmd = RSYNC_RSH;
		cmd = strdup(cmd);
		if (!cmd) 
			goto oom;

		for (tok=strtok(cmd," ");tok;tok=strtok(NULL," ")) {
			args[argc++] = tok;
		}

#if HAVE_REMSH
		/* remsh (on HPUX) takes the arguments the other way around */
		args[argc++] = machine;
		if (user) {
			args[argc++] = "-l";
			args[argc++] = user;
		}
#else
		if (user) {
			args[argc++] = "-l";
			args[argc++] = user;
		}
		args[argc++] = machine;
#endif

		args[argc++] = rsync_path;

		server_options(args,&argc);
	}

	args[argc++] = ".";

	if (path && *path) 
		args[argc++] = path;

	args[argc] = NULL;

	if (verbose > 3) {
		fprintf(FINFO,"cmd=");
		for (i=0;i<argc;i++)
			fprintf(FINFO,"%s ",args[i]);
		fprintf(FINFO,"\n");
	}

	if (local_server) {
		ret = local_child(argc, args, f_in, f_out);
	} else {
		ret = piped_child(args,f_in,f_out);
	}

	if (dir) free(dir);

	return ret;

oom:
	out_of_memory("do_cmd");
	return 0; /* not reached */
}