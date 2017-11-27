	int i;

	char *time_str = buffer;
	char *value_str = strchr (time_str, ':');
	if (value_str == NULL)
	{
		print_to_socket (fh, "-1 No time found.\n");
		return (-1);
	}
	*value_str = '\0'; value_str++;

	vl->time = (time_t) atoi (time_str);
	if (vl->time == 0)
