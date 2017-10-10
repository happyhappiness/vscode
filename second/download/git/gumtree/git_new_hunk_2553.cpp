		  : _("(no URL)"));

	for_each_string_list_item(item, &states.stale)
		string_list_append(&refs_to_prune, item->util);
	string_list_sort(&refs_to_prune);

	if (!dry_run)
		result |= delete_refs(&refs_to_prune);

	for_each_string_list_item(item, &states.stale) {
		const char *refname = item->util;

		if (dry_run)
			printf_ln(_(" * [would prune] %s"),
			       abbrev_ref(refname, "refs/remotes/"));
		else
			printf_ln(_(" * [pruned] %s"),
			       abbrev_ref(refname, "refs/remotes/"));
