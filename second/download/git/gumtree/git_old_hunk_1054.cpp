			   const char *refname, const unsigned char *sha1)
{
	struct packed_ref_cache *packed_ref_cache = get_packed_ref_cache(refs);

	if (!packed_ref_cache->lock)
		die("internal error: packed refs not locked");
	add_ref(get_packed_ref_dir(packed_ref_cache),
		create_ref_entry(refname, sha1, REF_ISPACKED, 1));
}

/*
 * Read the loose references from the namespace dirname into dir
 * (without recursing).  dirname must end with '/'.  dir must be the
 * directory entry corresponding to dirname.
 */
static void read_loose_refs(const char *dirname, struct ref_dir *dir)
{
	struct files_ref_store *refs = dir->ref_store;
	DIR *d;
	struct dirent *de;
	int dirnamelen = strlen(dirname);
	struct strbuf refname;
	struct strbuf path = STRBUF_INIT;
	size_t path_baselen;
	int err = 0;

	if (*refs->base.submodule)
		err = strbuf_git_path_submodule(&path, refs->base.submodule, "%s", dirname);
	else
		strbuf_git_path(&path, "%s", dirname);
	path_baselen = path.len;

	if (err) {
		strbuf_release(&path);
		return;
	}

	d = opendir(path.buf);
	if (!d) {
		strbuf_release(&path);
		return;
	}

