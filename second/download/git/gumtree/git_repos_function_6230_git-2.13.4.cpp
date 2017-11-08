static void submodules_absorb_gitdir_if_needed(const char *prefix)
{
	int i;
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
			absorb_git_dir_into_superproject(prefix, name,
				ABSORB_GITDIR_RECURSE_SUBMODULES);
	}
}