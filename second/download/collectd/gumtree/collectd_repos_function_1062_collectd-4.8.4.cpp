int global_option_set (const char *option, const char *value)
{
	int i;

	DEBUG ("option = %s; value = %s;", option, value);

	for (i = 0; i < cf_global_options_num; i++)
		if (strcasecmp (cf_global_options[i].key, option) == 0)
			break;

	if (i >= cf_global_options_num)
		return (-1);

	sfree (cf_global_options[i].value);

	if (value != NULL)
		cf_global_options[i].value = strdup (value);
	else
		cf_global_options[i].value = NULL;

	return (0);
}