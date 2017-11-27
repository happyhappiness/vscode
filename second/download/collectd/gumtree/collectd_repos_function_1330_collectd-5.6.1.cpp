static void free_zfs_values (kstat_t *ksp)
{
	if (ksp == NULL)
		return;

	for (llentry_t *e = llist_head (ksp); e != NULL; e = e->next)
	{
		sfree (e->key);
		sfree (e->value);
	}

	llist_destroy (ksp);
}