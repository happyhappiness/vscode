static void do_server_sender(int f_in, int f_out, int argc,char *argv[])
{
	int i;
	struct file_list *flist;
	char *dir = argv[0];
	extern int relative_paths;
	extern int am_daemon;
	extern int recurse;

	if (verbose > 2)
		rprintf(FINFO,"server_sender starting pid=%d\n",(int)getpid());
  
	if (!relative_paths && chdir(dir) != 0) {
		rprintf(FERROR,"chdir %s: %s (3)\n",dir,strerror(errno));
		exit_cleanup(1);
	}
	argc--;
	argv++;
  
	if (strcmp(dir,".")) {
		int l = strlen(dir);
		if (strcmp(dir,"/") == 0) 
			l = 0;
		for (i=0;i<argc;i++)
			argv[i] += l+1;
	}

	if (argc == 0 && recurse) {
		argc=1;
		argv--;
		argv[0] = ".";
	}
	
	flist = send_file_list(f_out,argc,argv);
	send_files(flist,f_out,f_in);
	report(f_out);
	exit_cleanup(0);
}