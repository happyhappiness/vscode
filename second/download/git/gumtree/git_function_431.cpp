static struct files_ref_store *files_downcast(
		struct ref_store *ref_store, int submodule_allowed,
		const char *caller)
{
	if (ref_store->be != &refs_be_files)
		die("BUG: ref_store is type \"%s\" not \"files\" in %s",
		    ref_store->be->name, caller);

	if (!submodule_allowed)
		assert_main_repository(ref_store, caller);

	return (struct files_ref_store *)ref_store;
}