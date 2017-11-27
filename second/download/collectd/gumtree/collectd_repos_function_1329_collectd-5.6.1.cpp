static long long get_zfs_value(kstat_t *ksp, const char *key)
{
	llentry_t *e;
	value_t *v;

	e = llist_search (ksp, key);
	if (e == NULL)
	{
		ERROR ("zfs_arc plugin: `llist_search` failed for key: '%s'.", key);
		return (-1);
	}

	v = e->value;
	return ((long long) v->derive);
}