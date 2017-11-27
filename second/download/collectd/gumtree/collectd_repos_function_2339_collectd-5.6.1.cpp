int ignorelist_add (ignorelist_t *il, const char *entry)
{
	size_t len;

	if (il == NULL)
	{
		DEBUG ("add called with ignorelist_t == NULL");
		return (1);
	}

	len = strlen (entry);

	/* append nothing */
	if (len == 0)
	{
		DEBUG("not appending: empty entry");
		return (1);
	}

#if HAVE_REGEX_H
	/* regex string is enclosed in "/.../" */
	if ((len > 2) && (entry[0] == '/') && entry[len - 1] == '/')
	{
		char *copy;
		int status;

		/* skip leading slash */
		copy = strdup (entry + 1);
		if (copy == NULL)
			return ENOMEM;

		/* trim trailing slash */
		copy[strlen (copy) - 1] = 0;

		status = ignorelist_append_regex (il, copy);
		sfree (copy);
		return status;
	}
#endif

	return ignorelist_append_string(il, entry);
}