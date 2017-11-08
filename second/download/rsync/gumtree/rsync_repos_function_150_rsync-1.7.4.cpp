void start_server(int argc, char *argv[])
{
      setup_protocol(STDOUT_FILENO,STDIN_FILENO);
	
      if (am_sender) {
	      recv_exclude_list(STDIN_FILENO);
	      if (cvs_exclude)
		      add_cvs_excludes();
	      do_server_sender(argc,argv);
      } else {
	      do_server_recv(argc,argv);
      }
      exit_cleanup(0);
}