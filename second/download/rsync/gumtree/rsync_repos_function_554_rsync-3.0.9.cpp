static int do_recv(int f_in, int f_out, char *local_name)
{
	int pid;
	int exit_code = 0;
	int error_pipe[2];

	/* The receiving side mustn't obey this, or an existing symlink that
	 * points to an identical file won't be replaced by the referent. */
	copy_links = copy_dirlinks = copy_unsafe_links = 0;

#ifdef SUPPORT_HARD_LINKS
	if (preserve_hard_links && !inc_recurse)
		match_hard_links(first_flist);
#endif

	if (fd_pair(error_pipe) < 0) {
		rsyserr(FERROR, errno, "pipe failed in do_recv");
		exit_cleanup(RERR_IPC);
	}

	io_flush(NORMAL_FLUSH);

	if ((pid = do_fork()) == -1) {
		rsyserr(FERROR, errno, "fork failed in do_recv");
		exit_cleanup(RERR_IPC);
	}

	if (pid == 0) {
		am_receiver = 1;

		close(error_pipe[0]);
		if (f_in != f_out)
			close(f_out);

		/* we can't let two processes write to the socket at one time */
		io_end_multiplex_out();

		/* set place to send errors */
		set_msg_fd_out(error_pipe[1]);
		io_start_buffering_out(error_pipe[1]);

		recv_files(f_in, local_name);
		io_flush(FULL_FLUSH);
		handle_stats(f_in);

		send_msg(MSG_DONE, "", 1, 0);
		write_varlong(error_pipe[1], stats.total_read, 3);
		io_flush(FULL_FLUSH);

		/* Handle any keep-alive packets from the post-processing work
		 * that the generator does. */
		if (protocol_version >= 29) {
			int iflags, xlen;
			uchar fnamecmp_type;
			char xname[MAXPATHLEN];

			kluge_around_eof = -1;

			/* This should only get stopped via a USR2 signal. */
			read_ndx_and_attrs(f_in, &iflags, &fnamecmp_type,
					   xname, &xlen);

			rprintf(FERROR, "Invalid packet at end of run [%s]\n",
				who_am_i());
			exit_cleanup(RERR_PROTOCOL);
		}

		/* Finally, we go to sleep until our parent kills us with a
		 * USR2 signal.  We sleep for a short time, as on some OSes
		 * a signal won't interrupt a sleep! */
		while (1)
			msleep(20);
	}

	am_generator = 1;

	io_end_multiplex_in();
	if (write_batch && !am_server)
		stop_write_batch();

	close(error_pipe[1]);
	if (f_in != f_out)
		close(f_in);

	io_start_buffering_out(f_out);

	set_msg_fd_in(error_pipe[0]);
	io_start_buffering_in(error_pipe[0]);

#ifdef SUPPORT_HARD_LINKS
	if (preserve_hard_links && inc_recurse) {
		struct file_list *flist;
		for (flist = first_flist; flist; flist = flist->next)
			match_hard_links(flist);
	}
#endif

	generate_files(f_out, local_name);

	handle_stats(-1);
	io_flush(FULL_FLUSH);
	if (protocol_version >= 24) {
		/* send a final goodbye message */
		write_ndx(f_out, NDX_DONE);
	}
	io_flush(FULL_FLUSH);

	set_msg_fd_in(-1);
	kill(pid, SIGUSR2);
	wait_process_with_flush(pid, &exit_code);
	return exit_code;
}