int global_option_set (const char *option, const char *value, _Bool from_cli)
{
	int i;
	DEBUG ("option = %s; value = %s;", option, value);

	for (i = 0; i < cf_global_options_num; i++)
		if (strcasecmp (cf_global_options[i].key, option) == 0)
			break;

	if (i >= cf_global_options_num)
	{
		ERROR ("configfile: Cannot set unknown global option `%s'.", option);
		return (-1);
	}

	if (cf_global_options[i].from_cli && (! from_cli))
	{
		DEBUG ("configfile: Ignoring %s `%s' option because "
				"it was overriden by a command-line option.",
				option, value);
		return (0);
	}

	sfree (cf_global_options[i].value);

	if (value != NULL)
		cf_global_options[i].value = strdup (value);
	else
		cf_global_options[i].value = NULL;

	cf_global_options[i].from_cli = from_cli;

	return (0);
}