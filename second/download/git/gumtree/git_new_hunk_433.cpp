
static const char * const update_index_usage[] = {
	N_("git update-index [<options>] [--] [<file>...]"),
	NULL
};

static struct object_id head_oid;
static struct object_id merge_head_oid;

static struct cache_entry *read_one_ent(const char *which,
					struct object_id *ent, const char *path,
					int namelen, int stage)
{
	unsigned mode;
	struct object_id oid;
	int size;
	struct cache_entry *ce;

	if (get_tree_entry(ent->hash, path, oid.hash, &mode)) {
		if (which)
			error("%s: not in %s branch.", path, which);
		return NULL;
	}
	if (mode == S_IFDIR) {
		if (which)
			error("%s: not a blob in %s branch.", path, which);
		return NULL;
	}
	size = cache_entry_size(namelen);
	ce = xcalloc(1, size);

	oidcpy(&ce->oid, &oid);
	memcpy(ce->name, path, namelen);
	ce->ce_flags = create_ce_flags(stage);
	ce->ce_namelen = namelen;
	ce->ce_mode = create_ce_mode(mode);
	return ce;
}
