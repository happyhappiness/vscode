int client_run(int f_in, int f_out, pid_t pid, int argc, char *argv[])
{
	struct file_list *flist = NULL;
	int exit_code = 0, exit_code2 = 0;
	char *local_name = NULL;

	cleanup_child_pid = pid;
	if (!read_batch) {
		set_nonblocking(f_in);
		set_nonblocking(f_out);
	}

	io_set_sock_fds(f_in, f_out);
	setup_protocol(f_out,f_in);
#if defined HAVE_ICONV_OPEN && defined HAVE_ICONV_H
	setup_iconv();
#endif

	if (protocol_version >= 23 && !read_batch)
		io_start_multiplex_in();

	/* We set our stderr file handle to blocking because ssh might have
	 * set it to non-blocking.  This can be particularly troublesome if
	 * stderr is a clone of stdout, because ssh would have set our stdout
	 * to non-blocking at the same time (which can easily cause us to lose
	 * output from our print statements).  This kluge shouldn't cause ssh
	 * any problems for how we use it.  Note also that we delayed setting
	 * this until after the above protocol setup so that we know for sure
	 * that ssh is done twiddling its file descriptors.  */
	set_blocking(STDERR_FILENO);

	if (am_sender) {
		keep_dirlinks = 0; /* Must be disabled on the sender. */
		io_start_buffering_out();
		if (!filesfrom_host)
			set_msg_fd_in(f_in);
		send_filter_list(f_out);
		if (filesfrom_host)
			filesfrom_fd = f_in;

		if (write_batch && !am_server)
			start_write_batch(f_out);
		flist = send_file_list(f_out, argc, argv);
		set_msg_fd_in(-1);
		if (verbose > 3)
			rprintf(FINFO,"file list sent\n");
		the_file_list = flist;

		io_flush(NORMAL_FLUSH);
		send_files(flist,f_out,f_in);
		io_flush(FULL_FLUSH);
		handle_stats(-1);
		if (protocol_version >= 24)
			read_final_goodbye(f_in, f_out);
		if (pid != -1) {
			if (verbose > 3)
				rprintf(FINFO,"client_run waiting on %d\n", (int) pid);
			io_flush(FULL_FLUSH);
			wait_process_with_flush(pid, &exit_code);
		}
		output_summary();
		io_flush(FULL_FLUSH);
		exit_cleanup(exit_code);
	}

	if (need_messages_from_generator && !read_batch)
		io_start_multiplex_out();

	if (argc == 0)
		list_only |= 1;

	send_filter_list(read_batch ? -1 : f_out);

	if (filesfrom_fd >= 0) {
		io_set_filesfrom_fds(filesfrom_fd, f_out);
		filesfrom_fd = -1;
	}

	if (write_batch && !am_server)
		start_write_batch(f_in);
	flist = recv_file_list(f_in);
	the_file_list = flist;

	if (flist && flist->count > 0) {
		local_name = get_local_name(flist, argv[0]);

		fix_basis_dirs();

		exit_code2 = do_recv(f_in, f_out, flist, local_name);
	} else {
		handle_stats(-1);
		output_summary();
	}

	if (pid != -1) {
		if (verbose > 3)
			rprintf(FINFO,"client_run2 waiting on %d\n", (int) pid);
		io_flush(FULL_FLUSH);
		wait_process_with_flush(pid, &exit_code);
	}

	return MAX(exit_code, exit_code2);
}