int ignorelist_match (ignorelist_t *il, const char *entry)
{
	ignorelist_item_t *traverse;

	/* if no entries, collect all */
	if ((il == NULL) || (il->head == NULL))
		return (0);

	if ((entry == NULL) || (strlen (entry) == 0))
		return (0);

	/* traverse list and check entries */
	for (traverse = il->head; traverse != NULL; traverse = traverse->next)
	{
#if HAVE_REGEX_H
		if (traverse->rmatch != NULL)
		{
			if (ignorelist_match_regex (traverse, entry))
				return (il->ignore);
		}
		else
#endif
		{
			if (ignorelist_match_string (traverse, entry))
				return (il->ignore);
		}
	} /* for traverse */

	return (1 - il->ignore);
}