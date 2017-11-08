struct ref_store *ref_store_init(const char *submodule)
{
	const char *be_name = "files";
	struct ref_storage_be *be = find_ref_storage_backend(be_name);

	if (!be)
		die("BUG: reference backend %s is unknown", be_name);

	if (!submodule || !*submodule)
		return be->init(NULL);
	else
		return be->init(submodule);
}