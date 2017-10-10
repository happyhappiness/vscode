	if (!remote)
		die(_("No such remote: %s"), argv[1]);

	known_remotes.to_delete = remote;
	for_each_remote(add_known_remote, &known_remotes);

	strbuf_addf(&buf, "remote.%s", remote->name);
	if (git_config_rename_section(buf.buf, NULL) < 1)
		return error(_("Could not remove config section '%s'"), buf.buf);

	read_branches();
	for (i = 0; i < branch_list.nr; i++) {
		struct string_list_item *item = branch_list.items + i;
		struct branch_info *info = item->util;
		if (info->remote_name && !strcmp(info->remote_name, remote->name)) {
			const char *keys[] = { "remote", "merge", NULL }, **k;
