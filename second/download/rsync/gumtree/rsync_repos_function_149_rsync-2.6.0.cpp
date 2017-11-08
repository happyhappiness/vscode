int open_socket_out_wrapped (char *host,
			     int port,
			     const char *bind_address,
			     int af_hint)
{
	char *prog;

	if ((prog = getenv ("RSYNC_CONNECT_PROG")) != NULL) 
		return sock_exec (prog);
	else 
		return open_socket_out (host, port, bind_address,
					af_hint);
}