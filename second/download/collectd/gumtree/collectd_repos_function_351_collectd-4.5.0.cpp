char *sstrdup (const char *s)
{
	char *r;

	if (s == NULL)
		return (NULL);

	if((r = strdup (s)) == NULL)
	{
		ERROR ("Not enough memory.");
		exit (3);
	}

	return (r);
}