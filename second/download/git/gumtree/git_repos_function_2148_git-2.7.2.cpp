static struct ref *get_refs_via_connect(struct transport *transport, int for_push)
{
	struct git_transport_data *data = transport->data;
	struct ref *refs;

	connect_setup(transport, for_push, 0);
	get_remote_heads(data->fd[0], NULL, 0, &refs,
			 for_push ? REF_NORMAL : 0,
			 &data->extra_have,
			 &data->shallow);
	data->got_remote_heads = 1;

	return refs;
}