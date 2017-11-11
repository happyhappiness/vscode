int client_run(int f_in, int f_out, pid_t pid, int argc, char *argv[])
{
	struct file_list *flist = NULL;
	int status = 0, status2 = 0;
	char *local_name = NULL;
	extern pid_t cleanup_child_pid;
	extern int write_batch;
	extern int read_batch;
	extern struct file_list *batch_flist;

	cleanup_child_pid = pid;
	if (read_batch)
		flist = batch_flist;

	set_nonblocking(f_in);
	set_nonblocking(f_out);

	setup_protocol(f_out,f_in);

	if (protocol_version >= 23)
		io_start_multiplex_in(f_in);

	if (am_sender) {
		extern int cvs_exclude;
		extern int delete_mode;
		extern int delete_excluded;
		if (cvs_exclude)
			add_cvs_excludes();
		if (delete_mode && !delete_excluded)
			send_exclude_list(f_out);
		if (remote_filesfrom_file)
			filesfrom_fd = f_in;
		if (!read_batch) /*  dw -- don't write to pipe */
			flist = send_file_list(f_out,argc,argv);
		if (verbose > 3)
			rprintf(FINFO,"file list sent\n");

		send_files(flist,f_out,f_in);
		if (protocol_version >= 24) {
			/* final goodbye message */
			read_int(f_in);
		}
		if (pid != -1) {
			if (verbose > 3)
				rprintf(FINFO,"client_run waiting on %d\n", (int) pid);
			io_flush();
			wait_process(pid, &status);
		}
		report(-1);
		exit_cleanup(status);
	}

	if (argc == 0) {
		extern int list_only;
		list_only = 1;
	}

	if (!write_batch)
		send_exclude_list(f_out);

	if (filesfrom_fd >= 0) {
		io_set_filesfrom_fds(filesfrom_fd, f_out);
		filesfrom_fd = -1;
	}

	flist = recv_file_list(f_in);
	if (!flist || flist->count == 0) {
		rprintf(FINFO, "client: nothing to do: "
			"perhaps you need to specify some filenames or "
			"the --recursive option?\n");
		exit_cleanup(0);
	}

	local_name = get_local_name(flist,argv[0]);

	status2 = do_recv(f_in,f_out,flist,local_name);

	if (pid != -1) {
		if (verbose > 3)
			rprintf(FINFO,"client_run2 waiting on %d\n", (int) pid);
		io_flush();
		wait_process(pid, &status);
	}

	return MAX(status, status2);
}