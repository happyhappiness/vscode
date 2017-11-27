const char *global_option_get (const char *option)
{
	int i;

	for (i = 0; i < cf_global_options_num; i++)
		if (strcasecmp (cf_global_options[i].key, option) == 0)
			break;

	if (i >= cf_global_options_num)
		return (NULL);
	
	return ((cf_global_options[i].value != NULL)
			? cf_global_options[i].value
			: cf_global_options[i].def);
}