static int interface_config (const char *key, const char *value)
{
	if (ignorelist == NULL)
		ignorelist = ignorelist_create (/* invert = */ 1);

	if (strcasecmp (key, "Interface") == 0)
	{
		ignorelist_add (ignorelist, value);
	}
	else if (strcasecmp (key, "IgnoreSelected") == 0)
	{
		int invert = 1;
		if ((strcasecmp (value, "True") == 0)
				|| (strcasecmp (value, "Yes") == 0)
				|| (strcasecmp (value, "On") == 0))
			invert = 0;
		ignorelist_set_invert (ignorelist, invert);
	}
	else
	{
		return (-1);
	}

	return (0);
}