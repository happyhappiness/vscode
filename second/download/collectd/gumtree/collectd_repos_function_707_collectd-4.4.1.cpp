int handle_flush (FILE *fh, char **fields, int fields_num)
{
	int success = 0;
	int error   = 0;

	int timeout = -1;

	int i;

	for (i = 1; i < fields_num; i++)
	{
		char *option = fields[i];
		int   status = 0;

		if (strncasecmp ("plugin=", option, strlen ("plugin=")) == 0)
		{
			char *plugin = option + strlen ("plugin=");

			if (0 == plugin_flush_one (timeout, plugin))
				++success;
			else
				++error;
		}
		else if (strncasecmp ("timeout=", option, strlen ("timeout=")) == 0)
		{
			char *endptr = NULL;
			char *value  = option + strlen ("timeout=");

			errno = 0;
			timeout = strtol (value, &endptr, 0);

			if ((endptr == value) || (0 != errno))
				status = -1;
			else if (0 >= timeout)
				timeout = -1;
		}
		else
			status = -1;

		if (status != 0)
		{
			print_to_socket (fh, "-1 Cannot parse option %s\n", option);
			return (-1);
		}
	}

	if ((success + error) > 0)
	{
		print_to_socket (fh, "0 Done: %i successful, %i errors\n",
				success, error);
	}
	else
	{
		plugin_flush_all (timeout);
		print_to_socket (fh, "0 Done\n");
	}

	return (0);
}