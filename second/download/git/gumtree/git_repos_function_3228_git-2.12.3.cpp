struct ref_store *lookup_ref_store(const char *submodule)
{
	struct ref_store *refs;

	if (!submodule || !*submodule)
		return main_ref_store;

	for (refs = submodule_ref_stores; refs; refs = refs->next) {
		if (!strcmp(submodule, refs->submodule))
			return refs;
	}

	return NULL;
}