void start_server(int f_in, int f_out, int argc, char *argv[])
{
	set_nonblocking(f_in);
	set_nonblocking(f_out);

	io_set_sock_fds(f_in, f_out);
	setup_protocol(f_out, f_in);

	if (protocol_version >= 23)
		io_start_multiplex_out();

	if (am_sender) {
		keep_dirlinks = 0; /* Must be disabled on the sender. */
		if (need_messages_from_generator)
			io_start_multiplex_in();
		recv_filter_list(f_in);
		do_server_sender(f_in, f_out, argc, argv);
	} else
		do_server_recv(f_in, f_out, argc, argv);
	exit_cleanup(0);
}