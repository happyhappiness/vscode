void oidset_clear(struct oidset *set)
{
	hashmap_free(&set->map, 1);
}