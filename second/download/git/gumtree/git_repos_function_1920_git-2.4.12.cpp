static int connect_setup(struct transport *transport, int for_push, int verbose)
{
	struct git_transport_data *data = transport->data;

	if (data->conn)
		return 0;

	data->conn = git_connect(data->fd, transport->url,
				 for_push ? data->options.receivepack :
				 data->options.uploadpack,
				 verbose ? CONNECT_VERBOSE : 0);

	return 0;
}