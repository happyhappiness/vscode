
struct ref_store *get_main_ref_store(void)
{
	if (main_ref_store)
		return main_ref_store;

	main_ref_store = ref_store_init(get_git_dir(),
					(REF_STORE_READ |
					 REF_STORE_WRITE |
					 REF_STORE_ODB |
					 REF_STORE_MAIN));
	return main_ref_store;
}

/*
 * Register the specified ref_store to be the one that should be used
 * for submodule. It is a fatal error to call this function twice for
 * the same submodule.
 */
static void register_submodule_ref_store(struct ref_store *refs,
					 const char *submodule)
{
	if (!submodule_ref_stores.tablesize)
		hashmap_init(&submodule_ref_stores, submodule_hash_cmp, 0);

	if (hashmap_put(&submodule_ref_stores,
			alloc_submodule_hash_entry(submodule, refs)))
		die("BUG: ref_store for submodule '%s' initialized twice",
		    submodule);
}

struct ref_store *get_submodule_ref_store(const char *submodule)
{
	struct strbuf submodule_sb = STRBUF_INIT;
	struct ref_store *refs;
