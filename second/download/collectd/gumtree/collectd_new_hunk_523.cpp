	il->head = item;
}

#if HAVE_REGEX_H
static int ignorelist_append_regex(ignorelist_t *il, const char *entry)
{
	int rcompile;
	regex_t *regtemp;
	int errsize;
	char *regerr = NULL;
	ignorelist_item_t *new;

	/* create buffer */
	if ((regtemp = malloc(sizeof(regex_t))) == NULL)
	{
		ERROR ("cannot allocate new config entry");
		return (1);
	}
	memset (regtemp, '\0', sizeof(regex_t));

	/* compile regex */
	if ((rcompile = regcomp (regtemp, entry, REG_EXTENDED)) != 0)
	{
		/* prepare message buffer */
		errsize = regerror(rcompile, regtemp, NULL, 0);
		if (errsize)
			regerr = smalloc(errsize);
		/* get error message */
		if (regerror (rcompile, regtemp, regerr, errsize))
		{
			fprintf (stderr, "Cannot compile regex %s: %i/%s",
					entry, rcompile, regerr);
			ERROR ("Cannot compile regex %s: %i/%s",
					entry, rcompile, regerr);
		}
		else
		{
			fprintf (stderr, "Cannot compile regex %s: %i",
					entry, rcompile);
			ERROR ("Cannot compile regex %s: %i",
					entry, rcompile);
		}

		if (errsize)
			sfree (regerr);
		regfree (regtemp);
		return (1);
	}
	DEBUG("regex compiled: %s - %i", entry, rcompile);

	/* create new entry */
	if ((new = malloc(sizeof(ignorelist_item_t))) == NULL)
	{
		ERROR ("cannot allocate new config entry");
		regfree (regtemp);
		return (1);
	}
	memset (new, '\0', sizeof(ignorelist_item_t));
	new->rmatch = regtemp;

	/* append new entry */
	ignorelist_append (il, new);

	return (0);
} /* int ignorelist_append_regex(ignorelist_t *il, const char *entry) */
#endif

static int ignorelist_append_string(ignorelist_t *il, const char *entry)
