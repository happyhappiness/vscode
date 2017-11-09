static int prune_remote(const char *remote, int dry_run)
{
	int result = 0;
	struct ref_states states;
	struct string_list refs_to_prune = STRING_LIST_INIT_NODUP;
	struct string_list_item *item;
	const char *dangling_msg = dry_run
		? _(" %s will become dangling!")
		: _(" %s has become dangling!");

	memset(&states, 0, sizeof(states));
	get_remote_ref_states(remote, &states, GET_REF_STATES);

	if (!states.stale.nr) {
		free_remote_ref_states(&states);
		return 0;
	}

	printf_ln(_("Pruning %s"), remote);
	printf_ln(_("URL: %s"),
		  states.remote->url_nr
		  ? states.remote->url[0]
		  : _("(no URL)"));

	for_each_string_list_item(item, &states.stale)
		string_list_append(&refs_to_prune, item->util);
	string_list_sort(&refs_to_prune);

	if (!dry_run)
		result |= delete_refs("remote: prune", &refs_to_prune, 0);

	for_each_string_list_item(item, &states.stale) {
		const char *refname = item->util;

		if (dry_run)
			printf_ln(_(" * [would prune] %s"),
			       abbrev_ref(refname, "refs/remotes/"));
		else
			printf_ln(_(" * [pruned] %s"),
			       abbrev_ref(refname, "refs/remotes/"));
	}

	warn_dangling_symrefs(stdout, dangling_msg, &refs_to_prune);

	string_list_clear(&refs_to_prune, 0);
	free_remote_ref_states(&states);
	return result;
}