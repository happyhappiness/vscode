void start_server(int f_in, int f_out, int argc, char *argv[])
{
	extern int cvs_exclude;
	extern int read_batch;

	setup_protocol(f_out, f_in);

	set_nonblocking(f_in);
	set_nonblocking(f_out);

	if (protocol_version >= 23)
		io_start_multiplex_out(f_out);

	if (am_sender) {
		if (!read_batch) {
			recv_exclude_list(f_in);
			if (cvs_exclude)
				add_cvs_excludes();
		}
		do_server_sender(f_in, f_out, argc, argv);
	} else {
		do_server_recv(f_in, f_out, argc, argv);
	}
	exit_cleanup(0);
}