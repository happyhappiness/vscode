static void do_server_recv(int f_in, int f_out, int argc,char *argv[])
{
	int status;
	struct file_list *flist;
	char *local_name=NULL;
	char *dir = NULL;
	extern int delete_mode;
	extern int delete_excluded;
	extern int am_daemon;
	extern int module_id;
	extern int am_sender;
	extern int read_batch;
	extern struct file_list *batch_flist;

	if (verbose > 2)
		rprintf(FINFO,"server_recv(%d) starting pid=%d\n",argc,(int)getpid());

	if (am_daemon && lp_read_only(module_id) && !am_sender) {
		rprintf(FERROR,"ERROR: module is read only\n");
		exit_cleanup(RERR_SYNTAX);
		return;
	}

	
	if (argc > 0) {
		dir = argv[0];
		argc--;
		argv++;
		if (!am_daemon && !push_dir(dir, 0)) {
			rprintf(FERROR,"push_dir %s : %s (4)\n",
				dir,strerror(errno));
			exit_cleanup(RERR_FILESELECT);
		}    
	}

	if (delete_mode && !delete_excluded)
		recv_exclude_list(f_in);

	if (read_batch)
	    flist = batch_flist;
	else
	    flist = recv_file_list(f_in);
	if (!flist) {
		rprintf(FERROR,"server_recv: recv_file_list error\n");
		exit_cleanup(RERR_FILESELECT);
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