void base_ref_store_init(struct ref_store *refs,
			 const struct ref_storage_be *be,
			 const char *submodule)
{
	refs->be = be;
	if (!submodule) {
		if (main_ref_store)
			die("BUG: main_ref_store initialized twice");

		refs->submodule = "";
		refs->next = NULL;
		main_ref_store = refs;
	} else {
		if (lookup_ref_store(submodule))
			die("BUG: ref_store for submodule '%s' initialized twice",
			    submodule);

		refs->submodule = xstrdup(submodule);
		refs->next = submodule_ref_stores;
		submodule_ref_stores = refs;
	}
}