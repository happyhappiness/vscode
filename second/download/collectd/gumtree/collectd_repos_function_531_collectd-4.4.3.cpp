static counter_list_t *counter_list_search (counter_list_t **list, unsigned int key)
{
	counter_list_t *entry;

	DEBUG ("counter_list_search (list = %p, key = %u)",
			(void *) *list, key);

	for (entry = *list; entry != NULL; entry = entry->next)
		if (entry->key == key)
			break;

	DEBUG ("return (%p)", (void *) entry);
	return (entry);
}