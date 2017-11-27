cu_tail_t *cu_tail_create (const char *file)
{
	cu_tail_t *obj;

	obj = (cu_tail_t *) malloc (sizeof (cu_tail_t));
	if (obj == NULL)
		return (NULL);
	memset (obj, '\0', sizeof (cu_tail_t));

	obj->file = strdup (file);
	if (obj->file == NULL)
	{
		free (obj);
		return (NULL);
	}

	obj->fh = NULL;

	return (obj);
}