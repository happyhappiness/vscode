void ping_destroy (pingobj_t *obj)
{
	pinghost_t *current;
	pinghost_t *next;

	current = obj->head;
	next = NULL;

	while (current != NULL)
	{
		next = current->next;
		ping_free (current);
		current = next;
	}

	if (obj->data != NULL)
		free (obj->data);

	free (obj);

	return;
}