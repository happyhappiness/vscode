static int checkout_path(unsigned mode, struct object_id *oid,
			 const char *path, const struct checkout *state)
{
	struct cache_entry *ce;
	int ret;

	ce = make_cache_entry(mode, oid->hash, path, 0, 0);
	ret = checkout_entry(ce, state, NULL);

	free(ce);
	return ret;
}