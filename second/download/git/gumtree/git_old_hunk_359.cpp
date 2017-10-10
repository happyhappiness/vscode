		    name, value, transport->url);
	if (r > 0)
		warning(_("Option \"%s\" is ignored for %s\n"),
			name, transport->url);
}

static struct transport *prepare_transport(struct remote *remote)
{
	struct transport *transport;
	transport = transport_get(remote, NULL);
	transport_set_verbosity(transport, verbosity, progress);
	transport->family = family;
	if (upload_pack)
		set_option(transport, TRANS_OPT_UPLOADPACK, upload_pack);
	if (keep)
		set_option(transport, TRANS_OPT_KEEP, "yes");
	if (depth)
		set_option(transport, TRANS_OPT_DEPTH, depth);
	if (update_shallow)
		set_option(transport, TRANS_OPT_UPDATE_SHALLOW, "yes");
	return transport;
}

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
