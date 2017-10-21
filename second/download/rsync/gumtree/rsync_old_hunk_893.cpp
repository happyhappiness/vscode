 **/
int open_socket_out_wrapped(char *host, int port, const char *bind_addr,
			    int af_hint)
{
	char *prog = getenv("RSYNC_CONNECT_PROG");

	if (verbose >= 2) {
		rprintf(FINFO, "%sopening tcp connection to %s port %d\n",
			prog ? "Using RSYNC_CONNECT_PROG instead of " : "",
			host, port);
	}
	if (prog)
