static void do_server_sender(int f_in, int f_out, int argc,char *argv[])
{
	int i;
	struct file_list *flist;
	char *dir = argv[0];
	extern int relative_paths;
	extern int recurse;
	extern int remote_version;

	if (verbose > 2)
		rprintf(FINFO,"server_sender starting pid=%d\n",(int)getpid());
  
	if (!relative_paths && !push_dir(dir, 0)) {
		rprintf(FERROR,"push_dir %s: %s (3)\n",dir,strerror(errno));
		exit_cleanup(RERR_FILESELECT);
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
	if (!flist || flist->count == 0) {
		exit_cleanup(0);
	}

	send_files(flist,f_out,f_in);
	io_flush();
	report(f_out);
	if (remote_version >= 24) {
		/* final goodbye message */		
 		read_int(f_in);
 	}
	io_flush();
	exit_cleanup(0);
}