static int parse_option (value_list_t *vl, char *buffer)
{
	char *option = buffer;
	char *value;

	if ((vl == NULL) || (option == NULL))
		return (-1);

	value = strchr (option, '=');
	if (value == NULL)
		return (-1);
	*value = '\0'; value++;

	if (strcasecmp ("interval", option) == 0)
	{
		vl->interval = atoi (value);
		if (vl->interval <= 0)
			vl->interval = interval_g;
	}
	else
		return (1);

	return (0);
}