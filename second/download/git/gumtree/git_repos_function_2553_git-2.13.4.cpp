void transport_unlock_pack(struct transport *transport)
{
	if (transport->pack_lockfile) {
		unlink_or_warn(transport->pack_lockfile);
		free(transport->pack_lockfile);
		transport->pack_lockfile = NULL;
	}
}