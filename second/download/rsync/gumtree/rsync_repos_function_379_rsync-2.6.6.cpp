static void do_server_sender(int f_in, int f_out, int argc,char *argv[])
{
	int i;
	struct file_list *flist;
	char *dir = argv[0];

	if (verbose > 2) {
		rprintf(FINFO, "server_sender starting pid=%ld\n",
			(long)getpid());
	}

	if (am_daemon && lp_write_only(module_id)) {
		rprintf(FERROR, "ERROR: module is write only\n");
		exit_cleanup(RERR_SYNTAX);
		return;
	}
	if (am_daemon && lp_read_only(module_id) && remove_sent_files) {
		rprintf(FERROR,
		    "ERROR: --remove-sent-files cannot be used with a read-only module\n");
		exit_cleanup(RERR_SYNTAX);
		return;
	}

	if (!relative_paths && !push_dir(dir)) {
		rsyserr(FERROR, errno, "push_dir#3 %s failed",
			full_fname(dir));
		exit_cleanup(RERR_FILESELECT);
	}
	argc--;
	argv++;

	if (strcmp(dir,".")) {
		int l = strlen(dir);
		if (strcmp(dir,"/") == 0)
			l = 0;
		for (i = 0; i < argc; i++)
			argv[i] += l+1;
	}

	if (argc == 0 && (recurse || list_only)) {
		argc = 1;
		argv--;
		argv[0] = ".";
	}

	flist = send_file_list(f_out,argc,argv);
	if (!flist || flist->count == 0) {
		exit_cleanup(0);
	}
	the_file_list = flist;

	io_start_buffering_in();
	io_start_buffering_out();

	send_files(flist,f_out,f_in);
	io_flush(FULL_FLUSH);
	handle_stats(f_out);
	if (protocol_version >= 24)
		read_final_goodbye(f_in, f_out);
	io_flush(FULL_FLUSH);
	exit_cleanup(0);
}