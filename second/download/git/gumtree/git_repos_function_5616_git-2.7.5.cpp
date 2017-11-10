static int check_submodules_use_gitfiles(void)
{
	int i;
	int errs = 0;
	struct string_list files = STRING_LIST_INIT_NODUP;

	for (i = 0; i < list.nr; i++) {
		const char *name = list.entry[i].name;
		int pos;
		const struct cache_entry *ce;

		pos = cache_name_pos(name, strlen(name));
		if (pos < 0) {
			pos = get_ours_cache_pos(name, pos);
			if (pos < 0)
				continue;
		}
		ce = active_cache[pos];

		if (!S_ISGITLINK(ce->ce_mode) ||
		    !file_exists(ce->name) ||
		    is_empty_dir(name))
			continue;

		if (!submodule_uses_gitfile(name))
			string_list_append(&files, name);
	}

	error_removing_concrete_submodules(&files, &errs);

	return errs;
}