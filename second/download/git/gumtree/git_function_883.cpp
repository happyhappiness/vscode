static struct files_ref_store *files_downcast(struct ref_store *ref_store,
					      unsigned int required_flags,
					      const char *caller)
{
	struct files_ref_store *refs;

	if (ref_store->be != &refs_be_files)
		die("BUG: ref_store is type \"%s\" not \"files\" in %s",
		    ref_store->be->name, caller);

	refs = (struct files_ref_store *)ref_store;

	if ((refs->store_flags & required_flags) != required_flags)
		die("BUG: operation %s requires abilities 0x%x, but only have 0x%x",
		    caller, required_flags, refs->store_flags);

	return refs;
}