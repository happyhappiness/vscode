static int push_refs(struct transport *transport,
		struct ref *remote_refs, int flags)
{
	struct helper_data *data = transport->data;

	if (process_connect(transport, 1)) {
		do_take_over(transport);
		return transport->push_refs(transport, remote_refs, flags);
	}

	if (!remote_refs) {
		fprintf(stderr, "No refs in common and none specified; doing nothing.\n"
			"Perhaps you should specify a branch such as 'master'.\n");
		return 0;
	}

	if (data->push)
		return push_refs_with_push(transport, remote_refs, flags);

	if (data->export)
		return push_refs_with_export(transport, remote_refs, flags);

	return -1;
}