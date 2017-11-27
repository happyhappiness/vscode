int cf_register_complex (const char *type, int (*callback) (oconfig_item_t *))
{
	cf_complex_callback_t *new;

	new = (cf_complex_callback_t *) malloc (sizeof (cf_complex_callback_t));
	if (new == NULL)
		return (-1);

	new->type = strdup (type);
	if (new->type == NULL)
	{
		sfree (new);
		return (-1);
	}

	new->callback = callback;
	new->next = NULL;

	if (complex_callback_head == NULL)
	{
		complex_callback_head = new;
	}
	else
	{
		cf_complex_callback_t *last = complex_callback_head;
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}

	return (0);
}