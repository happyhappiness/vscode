static struct ref *get_refs_from_bundle(struct transport *transport, int for_push)
{
	struct bundle_transport_data *data = transport->data;
	struct ref *result = NULL;
	int i;

	if (for_push)
		return NULL;

	if (data->fd > 0)
		close(data->fd);
	data->fd = read_bundle_header(transport->url, &data->header);
	if (data->fd < 0)
		die ("Could not read bundle '%s'.", transport->url);
	for (i = 0; i < data->header.references.nr; i++) {
		struct ref_list_entry *e = data->header.references.list + i;
		struct ref *ref = alloc_ref(e->name);
		hashcpy(ref->old_oid.hash, e->sha1);
		ref->next = result;
		result = ref;
	}
	return result;
}