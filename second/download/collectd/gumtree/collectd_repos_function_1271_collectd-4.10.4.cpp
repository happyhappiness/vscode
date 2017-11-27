static int set_option (value_list_t *vl, const char *key, const char *value)
{
	if ((vl == NULL) || (key == NULL) || (value == NULL))
		return (-1);

	if (strcasecmp ("interval", key) == 0)
	{
		int tmp;
		char *endptr;

		endptr = NULL;
		errno = 0;
		tmp = strtol (value, &endptr, 0);

		if ((errno == 0) && (endptr != NULL)
				&& (endptr != value) && (tmp > 0))
			vl->interval = tmp;
	}
	else
		return (1);

	return (0);
}