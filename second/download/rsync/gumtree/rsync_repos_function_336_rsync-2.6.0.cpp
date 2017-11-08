static int do_recv(int f_in,int f_out,struct file_list *flist,char *local_name)
{
	int pid;
	int status=0;
	int recv_pipe[2];
	int error_pipe[2];
	extern int preserve_hard_links;
	extern int delete_after;
	extern int recurse;
	extern int delete_mode;

	if (preserve_hard_links)
		init_hard_links(flist);

	if (!delete_after) {
		/* I moved this here from recv_files() to prevent a race condition */
		if (recurse && delete_mode && !local_name && flist->count>0) {
			delete_files(flist);
		}
	}

	if (fd_pair(recv_pipe) < 0) {
		rprintf(FERROR,"pipe failed in do_recv\n");
		exit_cleanup(RERR_SOCKETIO);
	}

	if (fd_pair(error_pipe) < 0) {
		rprintf(FERROR,"error pipe failed in do_recv\n");
		exit_cleanup(RERR_SOCKETIO);
	}

	io_flush();

	if ((pid=do_fork()) == 0) {
		close(recv_pipe[0]);
		close(error_pipe[0]);
		if (f_in != f_out) close(f_out);

		/* we can't let two processes write to the socket at one time */
		io_multiplexing_close();

		/* set place to send errors */
		set_error_fd(error_pipe[1]);

		recv_files(f_in,flist,local_name,recv_pipe[1]);
		io_flush();
		report(f_in);

		write_int(recv_pipe[1],1);
		close(recv_pipe[1]);
		io_flush();
		/* finally we go to sleep until our parent kills us
		 * with a USR2 signal. We sleep for a short time as on
		 * some OSes a signal won't interrupt a sleep! */
		while (msleep(20))
			;
	}

	close(recv_pipe[1]);
	close(error_pipe[1]);
	if (f_in != f_out) close(f_in);

	io_start_buffering(f_out);

	io_set_error_fd(error_pipe[0]);

	generate_files(f_out,flist,local_name,recv_pipe[0]);

	read_int(recv_pipe[0]);
	close(recv_pipe[0]);
	if (protocol_version >= 24) {
		/* send a final goodbye message */
		write_int(f_out, -1);
	}
	io_flush();

	io_set_error_fd(-1);
	kill(pid, SIGUSR2);
	wait_process(pid, &status);
	return status;
}