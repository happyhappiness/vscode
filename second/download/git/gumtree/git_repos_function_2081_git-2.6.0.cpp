void transport_take_over(struct transport *transport,
			 struct child_process *child)
{
	struct git_transport_data *data;

	if (!transport->smart_options)
		die("Bug detected: Taking over transport requires non-NULL "
		    "smart_options field.");

	data = xcalloc(1, sizeof(*data));
	data->options = *transport->smart_options;
	data->conn = child;
	data->fd[0] = data->conn->out;
	data->fd[1] = data->conn->in;
	data->got_remote_heads = 0;
	transport->data = data;

	transport->set_option = NULL;
	transport->get_refs_list = get_refs_via_connect;
	transport->fetch = fetch_refs_via_pack;
	transport->push = NULL;
	transport->push_refs = git_transport_push;
	transport->disconnect = disconnect_git;
	transport->smart_options = &(data->options);

	transport->cannot_reuse = 1;
}