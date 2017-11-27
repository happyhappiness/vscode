static counter_list_t *counter_list_create (counter_list_t **list,
		unsigned int key, unsigned int value)
{
	counter_list_t *entry;

	entry = (counter_list_t *) malloc (sizeof (counter_list_t));
	if (entry == NULL)
		return (NULL);

	memset (entry, 0, sizeof (counter_list_t));
	entry->key = key;
	entry->value = value;

	if (*list == NULL)
	{
		*list = entry;
	}
	else
	{
		counter_list_t *last;

		last = *list;
		while (last->next != NULL)
			last = last->next;

		last->next = entry;
	}

	return (entry);
}