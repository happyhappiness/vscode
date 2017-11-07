void git_configset_init(struct config_set *cs)
{
	hashmap_init(&cs->config_hash, (hashmap_cmp_fn)config_set_element_cmp, 0);
	cs->hash_initialized = 1;
	cs->list.nr = 0;
	cs->list.alloc = 0;
	cs->list.items = NULL;
}