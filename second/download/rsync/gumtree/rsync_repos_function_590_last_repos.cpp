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

	if (backup_dir) {
		STRUCT_STAT st;
		int ret;
		if (backup_dir_len > 1)
			backup_dir_buf[backup_dir_len-1] = '\0';
		ret = do_stat(backup_dir_buf, &st);
		if (ret != 0 || !S_ISDIR(st.st_mode)) {
			if (ret == 0) {
				rprintf(FERROR, "The backup-dir is not a directory: %s\n", backup_dir_buf);
				exit_cleanup(RERR_SYNTAX);
			}
			if (errno != ENOENT) {
				rprintf(FERROR, "Failed to stat %s: %s\n", backup_dir_buf, strerror(errno));
				exit_cleanup(RERR_FILEIO);
			}
			rprintf(FINFO, "(new) backup_dir is %s\n", backup_dir_buf);
		} else if (INFO_GTE(BACKUP, 1))
			rprintf(FINFO, "backup_dir is %s\n", backup_dir_buf);
		if (backup_dir_len > 1)
			backup_dir_buf[backup_dir_len-1] = '/';
	}

	io_flush(FULL_FLUSH);

	if ((pid = do_fork()) == -1) {
		rsyserr(FERROR, errno, "fork failed in do_recv");
		exit_cleanup(RERR_IPC);
	}

	if (pid == 0) {
		am_receiver = 1;
		send_msgs_to_gen = am_server;

		close(error_pipe[0]);

		/* We can't let two processes write to the socket at one time. */
		io_end_multiplex_out(MPLX_SWITCHING);
		if (f_in != f_out)
			close(f_out);
		sock_f_out = -1;
		f_out = error_pipe[1];

		bwlimit_writemax = 0; /* receiver doesn't need to do this */

		if (read_batch)
			io_start_buffering_in(f_in);
		io_start_multiplex_out(f_out);

		recv_files(f_in, f_out, local_name);
		io_flush(FULL_FLUSH);
		handle_stats(f_in);

		if (output_needs_newline) {
			fputc('\n', stdout);
			output_needs_newline = 0;
		}

		write_int(f_out, NDX_DONE);
		send_msg(MSG_STATS, (char*)&stats.total_read, sizeof stats.total_read, 0);
		io_flush(FULL_FLUSH);

		/* Handle any keep-alive packets from the post-processing work
		 * that the generator does. */
		if (protocol_version >= 29) {
			kluge_around_eof = -1;

			/* This should only get stopped via a USR2 signal. */
			read_final_goodbye(f_in, f_out);

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
	flist_receiving_enabled = True;

	io_end_multiplex_in(MPLX_SWITCHING);
	if (write_batch && !am_server)
		stop_write_batch();

	close(error_pipe[1]);
	if (f_in != f_out)
		close(f_in);
	sock_f_in = -1;
	f_in = error_pipe[0];

	io_start_buffering_out(f_out);
	io_start_multiplex_in(f_in);

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
	shutting_down = True;
	if (protocol_version >= 24) {
		/* send a final goodbye message */
		write_ndx(f_out, NDX_DONE);
	}
	io_flush(FULL_FLUSH);

	kill(pid, SIGUSR2);
	wait_process_with_flush(pid, &exit_code);
	return exit_code;
}