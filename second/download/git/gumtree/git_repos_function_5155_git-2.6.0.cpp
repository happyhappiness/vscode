static int add_remote_or_group(const char *name, struct string_list *list)
{
	int prev_nr = list->nr;
	struct remote_group_data g;
	g.name = name; g.list = list;

	git_config(get_remote_group, &g);
	if (list->nr == prev_nr) {
		struct remote *remote;
		if (!remote_is_configured(name))
			return 0;
		remote = remote_get(name);
		string_list_append(list, remote->name);
	}
	return 1;
}