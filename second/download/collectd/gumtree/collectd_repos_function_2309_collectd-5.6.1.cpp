llentry_t *llentry_create (char *key, void *value)
{
	llentry_t *e;

	e = malloc (sizeof (*e));
	if (e)
	{
		e->key   = key;
		e->value = value;
		e->next  = NULL;
	}

	return (e);
}