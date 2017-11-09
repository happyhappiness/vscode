void transport_unlock_pack(struct transport *transport)
{
	if (transport->pack_lockfile) {
		unlink_or_warn(transport->pack_lockfile);
		FREE_AND_NULL(transport->pack_lockfile);
	}
}