	namelen = strlen(patch->new_name);
	ce_size = cache_entry_size(namelen);
	mode = patch->new_mode ? patch->new_mode : (S_IFREG | 0644);

	remove_file_from_cache(patch->new_name);
	for (stage = 1; stage < 4; stage++) {
		if (is_null_sha1(patch->threeway_stage[stage - 1]))
			continue;
		ce = xcalloc(1, ce_size);
		memcpy(ce->name, patch->new_name, namelen);
		ce->ce_mode = create_ce_mode(mode);
		ce->ce_flags = create_ce_flags(stage);
		ce->ce_namelen = namelen;
		hashcpy(ce->sha1, patch->threeway_stage[stage - 1]);
		if (add_cache_entry(ce, ADD_CACHE_OK_TO_ADD) < 0)
			die(_("unable to add cache entry for %s"), patch->new_name);
	}
}

static void create_file(struct patch *patch)
