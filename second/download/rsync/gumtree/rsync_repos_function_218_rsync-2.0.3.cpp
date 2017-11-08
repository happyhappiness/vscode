static void do_server_recv(int f_in, int f_out, int argc,char *argv[])
{
	int status;
	struct file_list *flist;
	char *local_name=NULL;
	char *dir = NULL;
	extern int delete_mode;
	extern int am_daemon;

	if (verbose > 2)
		rprintf(FINFO,"server_recv(%d) starting pid=%d\n",argc,(int)getpid());
	
	if (argc > 0) {
		dir = argv[0];
		argc--;
		argv++;
		if (!am_daemon && chdir(dir) != 0) {
			rprintf(FERROR,"chdir %s : %s (4)\n",
				dir,strerror(errno));
			exit_cleanup(1);
		}    
	}

	if (delete_mode)
		recv_exclude_list(f_in);

	flist = recv_file_list(f_in);
	if (!flist || flist->count == 0) {
		rprintf(FERROR,"nothing to do\n");
		exit_cleanup(1);
	}
	
	if (argc > 0) {    
		if (strcmp(dir,".")) {
			argv[0] += strlen(dir);
			if (argv[0][0] == '/') argv[0]++;
		}
		local_name = get_local_name(flist,argv[0]);
	}

	status = do_recv(f_in,f_out,flist,local_name);
	exit_cleanup(status);
}