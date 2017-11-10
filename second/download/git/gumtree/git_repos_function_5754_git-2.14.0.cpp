static int add_remote_or_group(const char *name, struct string_list *list)
{
	int prev_nr = list->nr;
	struct remote_group_data g;
	g.name = name; g.list = list;

	git_config(get_remote_group, &g);
	if (list->nr == prev_nr) {
		struct remote *remote = remote_get(name);
		if (!remote_is_configured(remote, 0))
			return 0;
		string_list_append(list, remote->name);
	}
	return 1;
}