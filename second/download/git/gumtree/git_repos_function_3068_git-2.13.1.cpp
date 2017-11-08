static void reload_gitmodules_file(struct index_state *index,
				   struct checkout *state)
{
	int i;
	for (i = 0; i < index->cache_nr; i++) {
		struct cache_entry *ce = index->cache[i];
		if (ce->ce_flags & CE_UPDATE) {
			int r = strcmp(ce->name, ".gitmodules");
			if (r < 0)
				continue;
			else if (r == 0) {
				submodule_free();
				checkout_entry(ce, state, NULL);
				gitmodules_config();
				git_config(submodule_config, NULL);
			} else
				break;
		}
	}
}