int ignorelist_add (ignorelist_t *il, const char *entry)
{
	int ret;
	size_t entry_len;

	if (il == NULL)
	{
		DEBUG ("add called with ignorelist_t == NULL");
		return (1);
	}

	entry_len = strlen (entry);

	/* append nothing */
	if (entry_len == 0)
	{
		DEBUG("not appending: empty entry");
		return (1);
	}

#if HAVE_REGEX_H
	/* regex string is enclosed in "/.../" */
	if ((entry_len > 2) && (entry[0] == '/') && entry[entry_len - 1] == '/')
	{
		char *entry_copy;
		size_t entry_copy_size;

		/* We need to copy `entry' since it's const */
		entry_copy_size = entry_len - 1;
		entry_copy = smalloc (entry_copy_size);
		strncpy (entry_copy, entry + 1, entry_copy_size);
		entry_copy[entry_copy_size - 1] = 0;

		DEBUG("I'm about to add regex entry: %s", entry_copy);
		ret = ignorelist_append_regex(il, entry_copy);
		sfree (entry_copy);
	}
	else
#endif
	{
		DEBUG("to add entry: %s", entry);
		ret = ignorelist_append_string(il, entry);
	}

	return (ret);
}