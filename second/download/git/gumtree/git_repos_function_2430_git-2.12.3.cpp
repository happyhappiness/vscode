static int connect_setup(struct transport *transport, int for_push)
{
	struct git_transport_data *data = transport->data;
	int flags = transport->verbose > 0 ? CONNECT_VERBOSE : 0;

	if (data->conn)
		return 0;

	switch (transport->family) {
	case TRANSPORT_FAMILY_ALL: break;
	case TRANSPORT_FAMILY_IPV4: flags |= CONNECT_IPV4; break;
	case TRANSPORT_FAMILY_IPV6: flags |= CONNECT_IPV6; break;
	}

	data->conn = git_connect(data->fd, transport->url,
				 for_push ? data->options.receivepack :
				 data->options.uploadpack,
				 flags);

	return 0;
}