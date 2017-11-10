const struct ref *transport_get_remote_refs(struct transport *transport)
{
	if (!transport->got_remote_refs) {
		transport->remote_refs = transport->get_refs_list(transport, 0);
		transport->got_remote_refs = 1;
	}

	return transport->remote_refs;
}