static int add_conflicted_stages_file(struct apply_state *state,
				       struct patch *patch)
{
	int stage, namelen;
	unsigned ce_size, mode;
	struct cache_entry *ce;

	if (!state->update_index)
		return 0;
	namelen = strlen(patch->new_name);
	ce_size = cache_entry_size(namelen);
	mode = patch->new_mode ? patch->new_mode : (S_IFREG | 0644);

	remove_file_from_cache(patch->new_name);
	for (stage = 1; stage < 4; stage++) {
		if (is_null_oid(&patch->threeway_stage[stage - 1]))
			continue;
		ce = xcalloc(1, ce_size);
		memcpy(ce->name, patch->new_name, namelen);
		ce->ce_mode = create_ce_mode(mode);
		ce->ce_flags = create_ce_flags(stage);
		ce->ce_namelen = namelen;
		oidcpy(&ce->oid, &patch->threeway_stage[stage - 1]);
		if (add_cache_entry(ce, ADD_CACHE_OK_TO_ADD) < 0) {
			free(ce);
			return error(_("unable to add cache entry for %s"),
				     patch->new_name);
		}
	}

	return 0;
}