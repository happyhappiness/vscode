static char *hddtemp_get_major_minor (char *drive)
{
	hddname_t *list;
	char *ret;

	for (list = first_hddname; list != NULL; list = list->next)
		if (strcmp (drive, list->name) == 0)
			break;

	if (list == NULL)
	{
		DEBUG ("Don't know %s, keeping name as-is.", drive);
		return (strdup (drive));
	}

	if ((ret = (char *) malloc (128 * sizeof (char))) == NULL)
		return (NULL);

	if (snprintf (ret, 128, "%i-%i", list->major, list->minor) >= 128)
	{
		free (ret);
		return (NULL);
	}

	return (ret);
}