static int ignorelist_match_regex (ignorelist_item_t *item, const char *entry)
{
	assert ((item != NULL) && (item->rmatch != NULL)
			&& (entry != NULL) && (strlen (entry) > 0));

	/* match regex */
	if (regexec (item->rmatch, entry, 0, NULL, 0) == 0)
		return (1);

	return (0);
}