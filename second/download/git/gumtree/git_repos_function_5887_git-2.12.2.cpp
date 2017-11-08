static int get_remote_ref_states(const char *name,
				 struct ref_states *states,
				 int query)
{
	struct transport *transport;
	const struct ref *remote_refs;

	states->remote = remote_get(name);
	if (!states->remote)
		return error(_("No such remote: %s"), name);

	read_branches();

	if (query) {
		transport = transport_get(states->remote, states->remote->url_nr > 0 ?
			states->remote->url[0] : NULL);
		remote_refs = transport_get_remote_refs(transport);
		transport_disconnect(transport);

		states->queried = 1;
		if (query & GET_REF_STATES)
			get_ref_states(remote_refs, states);
		if (query & GET_HEAD_NAMES)
			get_head_names(remote_refs, states);
		if (query & GET_PUSH_REF_STATES)
			get_push_ref_states(remote_refs, states);
	} else {
		for_each_ref(append_ref_to_tracked_list, states);
		string_list_sort(&states->tracked);
		get_push_ref_states_noquery(states);
	}

	return 0;
}