static struct ref_cache *get_ref_cache(const char *submodule)
{
	struct ref_cache *refs = lookup_ref_cache(submodule);

	if (!refs) {
		struct strbuf submodule_sb = STRBUF_INIT;

		strbuf_addstr(&submodule_sb, submodule);
		if (is_nonbare_repository_dir(&submodule_sb))
			refs = create_ref_cache(submodule);
		strbuf_release(&submodule_sb);
	}

	return refs;
}