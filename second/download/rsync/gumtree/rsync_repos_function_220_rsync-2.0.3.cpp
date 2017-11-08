int client_run(int f_in, int f_out, int pid, int argc, char *argv[])
{
	struct file_list *flist;
	int status = 0, status2 = 0;
	char *local_name = NULL;
	extern int am_sender;

	setup_protocol(f_out,f_in);
	
	if (am_sender) {
		extern int cvs_exclude;
		extern int delete_mode;
		if (cvs_exclude)
			add_cvs_excludes();
		if (delete_mode) 
			send_exclude_list(f_out);
		flist = send_file_list(f_out,argc,argv);
		if (verbose > 3) 
			rprintf(FINFO,"file list sent\n");
		send_files(flist,f_out,f_in);
		if (pid != -1) {
			if (verbose > 3)
				rprintf(FINFO,"waiting on %d\n",pid);
			waitpid(pid, &status, 0);
		}
		report(-1);
		exit_cleanup(status);
	}
	
	send_exclude_list(f_out);
	
	flist = recv_file_list(f_in);
	if (!flist || flist->count == 0) {
		rprintf(FINFO,"nothing to do\n");
		exit_cleanup(0);
	}
	
	local_name = get_local_name(flist,argv[0]);
	
	status2 = do_recv(f_in,f_out,flist,local_name);
	
	report(f_in);
	
	if (pid != -1) {
		waitpid(pid, &status, 0);
	}
	
	return status | status2;
}