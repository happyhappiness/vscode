static int connect_helper(struct transport *transport, const char *name,
		   const char *exec, int fd[2])
{
	struct helper_data *data = transport->data;

	/* Get_helper so connect is inited. */
	get_helper(transport);
	if (!data->connect)
		die("Operation not supported by protocol.");

	if (!process_connect_service(transport, name, exec))
		die("Can't connect to subservice %s.", name);

	fd[0] = data->helper->out;
	fd[1] = data->helper->in;
	return 0;
}