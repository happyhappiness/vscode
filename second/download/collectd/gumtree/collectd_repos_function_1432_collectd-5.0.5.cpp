static int watchitem_find (const char *name)
{
	int max = STATIC_ARRAY_SIZE (specs);
	int i;

	for (i = 0; i < max; i++)
		if (strcasecmp (name, specs[i].name) == 0)
			return i;

	return -1;
}