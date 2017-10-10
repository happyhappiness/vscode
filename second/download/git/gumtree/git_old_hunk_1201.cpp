{
	const char *port = STR(DEFAULT_GIT_PORT);
	struct child_process *proxy;

	get_host_and_port(&host, &port);

	proxy = xmalloc(sizeof(*proxy));
	child_process_init(proxy);
	argv_array_push(&proxy->args, git_proxy_command);
	argv_array_push(&proxy->args, host);
	argv_array_push(&proxy->args, port);
	proxy->in = -1;
