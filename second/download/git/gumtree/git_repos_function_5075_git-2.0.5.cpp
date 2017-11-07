static struct ref_update *update_alloc(void)
{
	struct ref_update *update;

	/* Allocate and zero-init a struct ref_update */
	update = xcalloc(1, sizeof(*update));
	ALLOC_GROW(updates, updates_count + 1, updates_alloc);
	updates[updates_count++] = update;

	/* Store and reset accumulated options */
	update->flags = update_flags;
	update_flags = 0;

	return update;
}