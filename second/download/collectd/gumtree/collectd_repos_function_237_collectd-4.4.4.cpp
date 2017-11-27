static int interface_config (const char *key, const char *value)
{
	char **temp;

	if (strcasecmp (key, "Interface") == 0)
	{
		temp = (char **) realloc (if_list, (if_list_num + 1) * sizeof (char *));
		if (temp == NULL)
		{
			ERROR ("Cannot allocate more memory.");
			return (1);
		}
		if_list = temp;

		if ((if_list[if_list_num] = strdup (value)) == NULL)
		{
			ERROR ("Cannot allocate memory.");
			return (1);
		}
		if_list_num++;
	}
	else if (strcasecmp (key, "IgnoreSelected") == 0)
	{
		if ((strcasecmp (value, "True") == 0)
				|| (strcasecmp (value, "Yes") == 0)
				|| (strcasecmp (value, "On") == 0))
			if_list_action = 1;
		else
			if_list_action = 0;
	}
	else
	{
		return (-1);
	}

	return (0);
}