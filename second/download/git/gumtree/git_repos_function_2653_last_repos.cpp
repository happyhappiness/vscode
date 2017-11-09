static int disconnect_git(struct transport *transport)
{
	struct git_transport_data *data = transport->data;
	if (data->conn) {
		if (data->got_remote_heads)
			packet_flush(data->fd[1]);
		close(data->fd[0]);
		close(data->fd[1]);
		finish_connect(data->conn);
	}

	free(data);
	return 0;
}