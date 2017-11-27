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
		if (IS_TRUE (value))
			invert = 0;
		ignorelist_set_invert (ignorelist, invert);
	}
	else if (strcasecmp (key, "ReportInactive") == 0)
		report_inactive = IS_TRUE (value);
	else if (strcasecmp (key, "UniqueName") == 0)
	{
		#ifdef HAVE_LIBKSTAT
		if (IS_TRUE (value))
			unique_name = 1;
		#else
			WARNING ("interface plugin: the \"UniqueName\" option is only valid on Solaris.");
		#endif /* HAVE_LIBKSTAT */
	}
	else
	{
		return (-1);
	}

	return (0);
}