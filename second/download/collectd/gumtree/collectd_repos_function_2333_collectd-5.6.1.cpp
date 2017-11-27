static int ignorelist_append_string(ignorelist_t *il, const char *entry)
{
	ignorelist_item_t *new;

	/* create new entry */
	if ((new = calloc(1, sizeof (*new))) == NULL )
	{
		ERROR ("cannot allocate new entry");
		return (1);
	}
	new->smatch = sstrdup(entry);

	/* append new entry */
	ignorelist_append (il, new);

	return (0);
}