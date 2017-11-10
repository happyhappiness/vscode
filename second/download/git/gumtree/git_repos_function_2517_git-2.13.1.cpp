static int connect_git(struct transport *transport, const char *name,
		       const char *executable, int fd[2])
{
	struct git_transport_data *data = transport->data;
	data->conn = git_connect(data->fd, transport->url,
				 executable, 0);
	fd[0] = data->fd[0];
	fd[1] = data->fd[1];
	return 0;
}