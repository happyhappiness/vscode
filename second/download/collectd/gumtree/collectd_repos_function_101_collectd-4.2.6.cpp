llentry_t *llentry_create (const char *key, void *value)
{
	llentry_t *e;

	e = (llentry_t *) malloc (sizeof (llentry_t));
	if (e == NULL)
		return (NULL);

	e->key   = strdup (key);
	e->value = value;
	e->next  = NULL;

	if (e->key == NULL)
	{
		free (e);
		return (NULL);
	}

	return (e);
}