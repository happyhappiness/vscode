static void backfill_tags(struct transport *transport, struct ref *ref_map)
{
	if (transport->cannot_reuse) {
		gsecondary = prepare_transport(transport->remote);
		transport = gsecondary;
	}

	transport_set_option(transport, TRANS_OPT_FOLLOWTAGS, NULL);
	transport_set_option(transport, TRANS_OPT_DEPTH, "0");
	fetch_refs(transport, ref_map);

	if (gsecondary) {
		transport_disconnect(gsecondary);
		gsecondary = NULL;
	}
}