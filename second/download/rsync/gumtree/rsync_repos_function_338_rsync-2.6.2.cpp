static int do_recv(int f_in,int f_out,struct file_list *flist,char *local_name)
{
	int pid;
	int status=0;
	int error_pipe[2];

	if (preserve_hard_links)
		init_hard_links(flist);

	if (!delete_after) {
		/* I moved this here from recv_files() to prevent a race condition */
		if (recurse && delete_mode && !local_name && flist->count>0) {
			delete_files(flist);
		}
	}

	if (fd_pair(error_pipe) < 0) {
		rprintf(FERROR,"error pipe failed in do_recv\n");
		exit_cleanup(RERR_SOCKETIO);
	}

	io_flush(NORMAL_FLUSH);

	if ((pid=do_fork()) == 0) {
		close(error_pipe[0]);
		if (f_in != f_out) close(f_out);

		/* we can't let two processes write to the socket at one time */
		io_multiplexing_close();

		/* set place to send errors */
		set_msg_fd_out(error_pipe[1]);

		recv_files(f_in,flist,local_name);
		io_flush(FULL_FLUSH);
		report(f_in);

		send_msg(MSG_DONE, "", 0);
		io_flush(FULL_FLUSH);
		/* finally we go to sleep until our parent kills us
		 * with a USR2 signal. We sleep for a short time as on
		 * some OSes a signal won't interrupt a sleep! */
		while (1)
			msleep(20);
	}

	am_generator = 1;

	close(error_pipe[1]);
	if (f_in != f_out) close(f_in);

	io_start_buffering_out(f_out);

	set_msg_fd_in(error_pipe[0]);

	generate_files(f_out, flist, local_name);

	get_redo_num(); /* Read final MSG_DONE and any prior messages. */
	report(-1);
	io_flush(FULL_FLUSH);
	if (protocol_version >= 24) {
		/* send a final goodbye message */
		write_int(f_out, -1);
	}
	io_flush(FULL_FLUSH);

	set_msg_fd_in(-1);
	kill(pid, SIGUSR2);
	wait_process(pid, &status);
	return status;
}