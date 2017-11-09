struct ref_store *get_submodule_ref_store(const char *submodule)
{
	struct strbuf submodule_sb = STRBUF_INIT;
	struct ref_store *refs;
	int ret;

	if (!submodule || !*submodule) {
		/*
		 * FIXME: This case is ideally not allowed. But that
		 * can't happen until we clean up all the callers.
		 */
		return get_main_ref_store();
	}

	refs = lookup_ref_store_map(&submodule_ref_stores, submodule);
	if (refs)
		return refs;

	strbuf_addstr(&submodule_sb, submodule);
	ret = is_nonbare_repository_dir(&submodule_sb);
	strbuf_release(&submodule_sb);
	if (!ret)
		return NULL;

	ret = submodule_to_gitdir(&submodule_sb, submodule);
	if (ret) {
		strbuf_release(&submodule_sb);
		return NULL;
	}

	/* assume that add_submodule_odb() has been called */
	refs = ref_store_init(submodule_sb.buf,
			      REF_STORE_READ | REF_STORE_ODB);
	register_ref_store_map(&submodule_ref_stores, "submodule",
			       refs, submodule);

	strbuf_release(&submodule_sb);
	return refs;
}