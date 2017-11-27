static int ignorelist_append_string(ignorelist_t *il, const char *entry)
{
	ignorelist_item_t *new;

	/* create new entry */
	if ((new = malloc(sizeof(ignorelist_item_t))) == NULL )
	{
		ERROR ("cannot allocate new entry");
		return (1);
	}
	memset (new, '\0', sizeof(ignorelist_item_t));
	new->smatch = sstrdup(entry);

	/* append new entry */
	ignorelist_append (il, new);

	return (0);
}