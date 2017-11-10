static const struct submodule *config_from(struct submodule_cache *cache,
		const unsigned char *commit_sha1, const char *key,
		enum lookup_type lookup_type)
{
	struct strbuf rev = STRBUF_INIT;
	unsigned long config_size;
	char *config;
	unsigned char sha1[20];
	enum object_type type;
	const struct submodule *submodule = NULL;
	struct parse_config_parameter parameter;

	/*
	 * If any parameter except the cache is a NULL pointer just
	 * return the first submodule. Can be used to check whether
	 * there are any submodules parsed.
	 */
	if (!commit_sha1 || !key) {
		struct hashmap_iter iter;
		struct submodule_entry *entry;

		hashmap_iter_init(&cache->for_name, &iter);
		entry = hashmap_iter_next(&iter);
		if (!entry)
			return NULL;
		return entry->config;
	}

	if (!gitmodule_sha1_from_commit(commit_sha1, sha1))
		return NULL;

	switch (lookup_type) {
	case lookup_name:
		submodule = cache_lookup_name(cache, sha1, key);
		break;
	case lookup_path:
		submodule = cache_lookup_path(cache, sha1, key);
		break;
	}
	if (submodule)
		return submodule;

	config = read_sha1_file(sha1, &type, &config_size);
	if (!config)
		return NULL;

	if (type != OBJ_BLOB) {
		free(config);
		return NULL;
	}

	/* fill the submodule config into the cache */
	parameter.cache = cache;
	parameter.commit_sha1 = commit_sha1;
	parameter.gitmodules_sha1 = sha1;
	parameter.overwrite = 0;
	git_config_from_buf(parse_config, rev.buf, config, config_size,
			&parameter);
	free(config);

	switch (lookup_type) {
	case lookup_name:
		return cache_lookup_name(cache, sha1, key);
	case lookup_path:
		return cache_lookup_path(cache, sha1, key);
	default:
		return NULL;
	}
}