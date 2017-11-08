static int show_remote_info_item(struct string_list_item *item, void *cb_data)
{
	struct show_info *info = cb_data;
	struct ref_states *states = info->states;
	const char *name = item->string;

	if (states->queried) {
		const char *fmt = "%s";
		const char *arg = "";
		if (string_list_has_string(&states->new, name)) {
			fmt = _(" new (next fetch will store in remotes/%s)");
			arg = states->remote->name;
		} else if (string_list_has_string(&states->tracked, name))
			arg = _(" tracked");
		else if (string_list_has_string(&states->stale, name))
			arg = _(" stale (use 'git remote prune' to remove)");
		else
			arg = _(" ???");
		printf("    %-*s", info->width, name);
		printf(fmt, arg);
		printf("\n");
	} else
		printf("    %s\n", name);

	return 0;
}