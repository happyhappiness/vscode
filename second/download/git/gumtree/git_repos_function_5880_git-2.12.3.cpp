static int get_ref_states(const struct ref *remote_refs, struct ref_states *states)
{
	struct ref *fetch_map = NULL, **tail = &fetch_map;
	struct ref *ref, *stale_refs;
	int i;

	for (i = 0; i < states->remote->fetch_refspec_nr; i++)
		if (get_fetch_map(remote_refs, states->remote->fetch + i, &tail, 1))
			die(_("Could not get fetch map for refspec %s"),
				states->remote->fetch_refspec[i]);

	states->new.strdup_strings = 1;
	states->tracked.strdup_strings = 1;
	states->stale.strdup_strings = 1;
	for (ref = fetch_map; ref; ref = ref->next) {
		if (!ref->peer_ref || !ref_exists(ref->peer_ref->name))
			string_list_append(&states->new, abbrev_branch(ref->name));
		else
			string_list_append(&states->tracked, abbrev_branch(ref->name));
	}
	stale_refs = get_stale_heads(states->remote->fetch,
				     states->remote->fetch_refspec_nr, fetch_map);
	for (ref = stale_refs; ref; ref = ref->next) {
		struct string_list_item *item =
			string_list_append(&states->stale, abbrev_branch(ref->name));
		item->util = xstrdup(ref->name);
	}
	free_refs(stale_refs);
	free_refs(fetch_map);

	string_list_sort(&states->new);
	string_list_sort(&states->tracked);
	string_list_sort(&states->stale);

	return 0;
}