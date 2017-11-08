static struct ref_store *files_ref_store_create(const char *submodule)
{
	struct files_ref_store *refs = xcalloc(1, sizeof(*refs));
	struct ref_store *ref_store = (struct ref_store *)refs;

	base_ref_store_init(ref_store, &refs_be_files, submodule);

	return ref_store;
}