static int fetch(struct transport *transport,
		 int nr_heads, struct ref **to_fetch)
{
	struct helper_data *data = transport->data;
	int i, count;

	if (process_connect(transport, 0)) {
		do_take_over(transport);
		return transport->fetch(transport, nr_heads, to_fetch);
	}

	count = 0;
	for (i = 0; i < nr_heads; i++)
		if (!(to_fetch[i]->status & REF_STATUS_UPTODATE))
			count++;

	if (!count)
		return 0;

	if (data->fetch)
		return fetch_with_fetch(transport, nr_heads, to_fetch);

	if (data->import)
		return fetch_with_import(transport, nr_heads, to_fetch);

	return -1;
}