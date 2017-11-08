static struct submodule *lookup_or_create_by_name(struct submodule_cache *cache,
		const unsigned char *gitmodules_sha1, const char *name)
{
	struct submodule *submodule;
	struct strbuf name_buf = STRBUF_INIT;

	submodule = cache_lookup_name(cache, gitmodules_sha1, name);
	if (submodule)
		return submodule;

	submodule = xmalloc(sizeof(*submodule));

	strbuf_addstr(&name_buf, name);
	submodule->name = strbuf_detach(&name_buf, NULL);

	submodule->path = NULL;
	submodule->url = NULL;
	submodule->fetch_recurse = RECURSE_SUBMODULES_NONE;
	submodule->ignore = NULL;

	hashcpy(submodule->gitmodules_sha1, gitmodules_sha1);

	cache_add(cache, submodule);

	return submodule;
}