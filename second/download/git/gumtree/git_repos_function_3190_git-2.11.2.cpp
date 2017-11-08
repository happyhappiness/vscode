struct ref_store *get_ref_store(const char *submodule)
{
	struct ref_store *refs;

	if (!submodule || !*submodule) {
		refs = lookup_ref_store(NULL);

		if (!refs)
			refs = ref_store_init(NULL);
	} else {
		refs = lookup_ref_store(submodule);

		if (!refs) {
			struct strbuf submodule_sb = STRBUF_INIT;

			strbuf_addstr(&submodule_sb, submodule);
			if (is_nonbare_repository_dir(&submodule_sb))
				refs = ref_store_init(submodule);
			strbuf_release(&submodule_sb);
		}
	}

	return refs;
}