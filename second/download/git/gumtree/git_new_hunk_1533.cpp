
struct ref_store *get_main_ref_store(void)
{
	if (main_ref_store)
		return main_ref_store;

	main_ref_store = ref_store_init(get_git_dir(), REF_STORE_ALL_CAPS);
	return main_ref_store;
}

/*
 * Associate a ref store with a name. It is a fatal error to call this
 * function twice for the same name.
 */
static void register_ref_store_map(struct hashmap *map,
				   const char *type,
				   struct ref_store *refs,
				   const char *name)
{
	if (!map->tablesize)
		hashmap_init(map, ref_store_hash_cmp, NULL, 0);

	if (hashmap_put(map, alloc_ref_store_hash_entry(name, refs)))
		die("BUG: %s ref_store '%s' initialized twice", type, name);
}

struct ref_store *get_submodule_ref_store(const char *submodule)
{
	struct strbuf submodule_sb = STRBUF_INIT;
	struct ref_store *refs;
