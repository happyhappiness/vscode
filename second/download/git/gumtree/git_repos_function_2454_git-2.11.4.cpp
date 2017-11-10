int transport_disconnect(struct transport *transport)
{
	int ret = 0;
	if (transport->disconnect)
		ret = transport->disconnect(transport);
	free(transport);
	return ret;
}