static int ignorelist_append_regex(ignorelist_t *il, const char *entry)
{
	regex_t *re;
	ignorelist_item_t *item;
	int status;

	/* create buffer */
	re = malloc (sizeof (*re));
	if (re == NULL)
	{
		ERROR ("ignorelist_append_regex: malloc failed.");
		return ENOMEM;
	}
	memset (re, 0, sizeof (*re));

	/* compile regex */
	status = regcomp (re, entry, REG_EXTENDED);
	if (status != 0)
	{
		char errbuf[1024];

		(void) regerror (status, re, errbuf, sizeof (errbuf));
		ERROR ("ignorelist_append_regex: Compiling regular expression \"%s\" failed: %s", entry, errbuf);
		sfree (re);
		return status;
	}

	/* create new entry */
	item = malloc (sizeof (*item));
	if (item == NULL)
	{
		ERROR ("ignorelist_append_regex: malloc failed.");
		regfree (re);
		sfree (re);
		return ENOMEM;
	}
	memset (item, 0, sizeof (*item));
	item->rmatch = re;

	/* append new entry */
	ignorelist_append (il, item);

	return (0);
}