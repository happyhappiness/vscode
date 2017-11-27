static int us_config (const char *key, const char *val)
{
	if (strcasecmp (key, "SocketFile") == 0)
	{
		char *new_sock_file = strdup (val);
		if (new_sock_file == NULL)
			return (1);

		sfree (sock_file);
		sock_file = new_sock_file;
	}
	else if (strcasecmp (key, "SocketGroup") == 0)
	{
		char *new_sock_group = strdup (val);
		if (new_sock_group == NULL)
			return (1);

		sfree (sock_group);
		sock_group = new_sock_group;
	}
	else if (strcasecmp (key, "SocketPerms") == 0)
	{
		sock_perms = (int) strtol (val, NULL, 8);
	}
	else if (strcasecmp (key, "DeleteSocket") == 0)
	{
		if (IS_TRUE (val))
			delete_socket = 1;
		else
			delete_socket = 0;
	}
	else
	{
		return (-1);
	}

	return (0);
}