static zone_stats_t *
zone_find_stats(c_avl_tree_t *tree, zoneid_t zoneid)
{
	zone_stats_t *ret = NULL;
	zoneid_t     *key = NULL;

	if (c_avl_get(tree, (void **)&zoneid, (void **)&ret)) {
		if (!(ret = malloc(sizeof(*ret)))) {
			WARNING("zone plugin: no memory");
			return(NULL);
		}
		if (!(key = malloc(sizeof(*key)))) {
			WARNING("zone plugin: no memory");
			free(ret);
			return(NULL);
		}
		*key = zoneid;
		if (c_avl_insert(tree, key, ret)) {
			WARNING("zone plugin: error inserting into tree");
			return(NULL);
		}
	}
	return(ret);
}