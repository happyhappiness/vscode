static int config_read_branches(const char *key, const char *value, void *cb)
{
	if (starts_with(key, "branch.")) {
		const char *orig_key = key;
		char *name;
		struct string_list_item *item;
		struct branch_info *info;
		enum { REMOTE, MERGE, REBASE } type;
		size_t key_len;

		key += 7;
		if (strip_suffix(key, ".remote", &key_len)) {
			name = xmemdupz(key, key_len);
			type = REMOTE;
		} else if (strip_suffix(key, ".merge", &key_len)) {
			name = xmemdupz(key, key_len);
			type = MERGE;
		} else if (strip_suffix(key, ".rebase", &key_len)) {
			name = xmemdupz(key, key_len);
			type = REBASE;
		} else
			return 0;

		item = string_list_insert(&branch_list, name);

		if (!item->util)
			item->util = xcalloc(1, sizeof(struct branch_info));
		info = item->util;
		if (type == REMOTE) {
			if (info->remote_name)
				warning(_("more than one %s"), orig_key);
			info->remote_name = xstrdup(value);
		} else if (type == MERGE) {
			char *space = strchr(value, ' ');
			value = abbrev_branch(value);
			while (space) {
				char *merge;
				merge = xstrndup(value, space - value);
				string_list_append(&info->merge, merge);
				value = abbrev_branch(space + 1);
				space = strchr(value, ' ');
			}
			string_list_append(&info->merge, xstrdup(value));
		} else {
			int v = git_config_maybe_bool(orig_key, value);
			if (v >= 0)
				info->rebase = v;
			else if (!strcmp(value, "preserve"))
				info->rebase = NORMAL_REBASE;
			else if (!strcmp(value, "interactive"))
				info->rebase = INTERACTIVE_REBASE;
		}
	}
	return 0;
}