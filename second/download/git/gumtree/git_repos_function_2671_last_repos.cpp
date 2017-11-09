int transport_connect(struct transport *transport, const char *name,
		      const char *exec, int fd[2])
{
	if (transport->connect)
		return transport->connect(transport, name, exec, fd);
	else
		die("Operation not supported by protocol");
}