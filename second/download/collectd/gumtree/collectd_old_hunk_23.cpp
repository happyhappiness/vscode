			regerr = smalloc(errsize);
		/* get error message */
		if (regerror (rcompile, regtemp, regerr, errsize))
		{
			fprintf (stderr, "Cannot compile regex %s: %i/%s",
					entry, rcompile, regerr);
			syslog (LOG_ERR, "Cannot compile regex %s: %i/%s",
					entry, rcompile, regerr);
		}
		else
		{
			fprintf (stderr, "Cannot compile regex %s: %i",
					entry, rcompile);
			syslog (LOG_ERR, "Cannot compile regex %s: %i",
					entry, rcompile);
		}

		if (errsize)
			sfree (regerr);
		regfree (regtemp);
		return (1);
	}
	DBG("regex compiled: %s - %i", entry, rcompile);

	/* create new entry */
	if ((new = malloc(sizeof(ignorelist_item_t))) == NULL)
	{
		syslog (LOG_ERR, "cannot allocate new config entry");
		regfree (regtemp);
		return (1);
	}
	memset (new, '\0', sizeof(ignorelist_item_t));
	new->rmatch = regtemp;

