static int do_recv(int f_in,int f_out,struct file_list *flist,char *local_name)
{
	int pid;
	int status=0;
	int recv_pipe[2];
	extern int preserve_hard_links;

	if (preserve_hard_links)
		init_hard_links(flist);

	if (pipe(recv_pipe) < 0) {
		rprintf(FERROR,"pipe failed in do_recv\n");
		exit_cleanup(1);
	}
  
	io_flush();

	if ((pid=do_fork()) == 0) {
		close(recv_pipe[0]);
		if (f_in != f_out) close(f_out);

		set_nonblocking(f_in);

		recv_files(f_in,flist,local_name,recv_pipe[1]);
		report(f_in);

		if (verbose > 3)
			rprintf(FINFO,"do_recv waiting on %d\n",pid);

		io_flush();
		_exit(0);
	}

	close(recv_pipe[1]);
	io_close_input(f_in);
	if (f_in != f_out) close(f_in);

	set_nonblocking(f_out);

	generate_files(f_out,flist,local_name,recv_pipe[0]);

	io_flush();
	waitpid(pid, &status, 0);
	return status;
}