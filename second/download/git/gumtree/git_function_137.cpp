static struct child_process *git_proxy_connect(int fd[2], char *host)
{
	const char *port = STR(DEFAULT_GIT_PORT);
	const char **argv;
	struct child_process *proxy;

	get_host_and_port(&host, &port);

	argv = xmalloc(sizeof(*argv) * 4);
	argv[0] = git_proxy_command;
	argv[1] = host;
	argv[2] = port;
	argv[3] = NULL;
	proxy = xcalloc(1, sizeof(*proxy));
	proxy->argv = argv;
	proxy->in = -1;
	proxy->out = -1;
	if (start_command(proxy))
		die("cannot start proxy %s", argv[0]);
	fd[0] = proxy->out; /* read from proxy stdout */
	fd[1] = proxy->in;  /* write to proxy stdin */
	return proxy;
}