static int fetch_refs(struct transport *transport, struct ref *ref_map)
{
	int ret = quickfetch(ref_map);
	if (ret)
		ret = transport_fetch_refs(transport, ref_map);
	if (!ret)
		ret |= store_updated_refs(transport->url,
				transport->remote->name,
				ref_map);
	transport_unlock_pack(transport);
	return ret;
}