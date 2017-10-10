
static const char * const update_index_usage[] = {
	N_("git update-index [<options>] [--] [<file>...]"),
	NULL
};

static unsigned char head_sha1[20];
static unsigned char merge_head_sha1[20];

static struct cache_entry *read_one_ent(const char *which,
					unsigned char *ent, const char *path,
					int namelen, int stage)
{
	unsigned mode;
	unsigned char sha1[20];
	int size;
	struct cache_entry *ce;

	if (get_tree_entry(ent, path, sha1, &mode)) {
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

	hashcpy(ce->sha1, sha1);
	memcpy(ce->name, path, namelen);
	ce->ce_flags = create_ce_flags(stage);
	ce->ce_namelen = namelen;
	ce->ce_mode = create_ce_mode(mode);
	return ce;
}
