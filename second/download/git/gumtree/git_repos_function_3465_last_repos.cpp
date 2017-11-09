static struct ref_store *ref_store_init(const char *gitdir,
					unsigned int flags)
{
	const char *be_name = "files";
	struct ref_storage_be *be = find_ref_storage_backend(be_name);
	struct ref_store *refs;

	if (!be)
		die("BUG: reference backend %s is unknown", be_name);

	refs = be->init(gitdir, flags);
	return refs;
}