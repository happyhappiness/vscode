void start_server(int f_in, int f_out, int argc, char *argv[])
{
	extern int cvs_exclude;
	extern int am_sender;

	setup_protocol(f_out, f_in);
	
	if (am_sender) {
		recv_exclude_list(f_in);
		if (cvs_exclude)
			add_cvs_excludes();
		do_server_sender(f_in, f_out, argc, argv);
	} else {
		do_server_recv(f_in, f_out, argc, argv);
	}
	exit_cleanup(0);
}