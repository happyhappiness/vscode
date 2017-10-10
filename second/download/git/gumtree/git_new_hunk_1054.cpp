			   const char *refname, const unsigned char *sha1)
{
	struct packed_ref_cache *packed_ref_cache = get_packed_ref_cache(refs);

	if (!packed_ref_cache->lock)
		die("internal error: packed refs not locked");
	add_ref_entry(get_packed_ref_dir(packed_ref_cache),
		      create_ref_entry(refname, sha1, REF_ISPACKED, 1));
}

/*
 * Read the loose references from the namespace dirname into dir
 * (without recursing).  dirname must end with '/'.  dir must be the
 * directory entry corresponding to dirname.
 */
static void loose_fill_ref_dir(struct ref_store *ref_store,
			       struct ref_dir *dir, const char *dirname)
{
	struct files_ref_store *refs =
		files_downcast(ref_store, REF_STORE_READ, "fill_ref_dir");
	DIR *d;
	struct dirent *de;
	int dirnamelen = strlen(dirname);
	struct strbuf refname;
	struct strbuf path = STRBUF_INIT;
	size_t path_baselen;

	files_ref_path(refs, &path, dirname);
	path_baselen = path.len;

	d = opendir(path.buf);
	if (!d) {
		strbuf_release(&path);
		return;
	}

