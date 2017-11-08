static struct ref_store *files_ref_store_create(const char *gitdir,
						unsigned int flags)
{
	struct files_ref_store *refs = xcalloc(1, sizeof(*refs));
	struct ref_store *ref_store = (struct ref_store *)refs;
	struct strbuf sb = STRBUF_INIT;

	base_ref_store_init(ref_store, &refs_be_files);
	refs->store_flags = flags;

	refs->gitdir = xstrdup(gitdir);
	get_common_dir_noenv(&sb, gitdir);
	refs->gitcommondir = strbuf_detach(&sb, NULL);
	strbuf_addf(&sb, "%s/packed-refs", refs->gitcommondir);
	refs->packed_refs_path = strbuf_detach(&sb, NULL);

	return ref_store;
}