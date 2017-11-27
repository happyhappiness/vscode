static int us_config (const char *key, const char *val)
{
	if (strcasecmp (key, "SocketFile") == 0)
	{
		sfree (sock_file);
		sock_file = strdup (val);
	}
	else if (strcasecmp (key, "SocketGroup") == 0)
	{
		sfree (sock_group);
		sock_group = strdup (val);
	}
	else if (strcasecmp (key, "SocketPerms") == 0)
	{
		sock_perms = (int) strtol (val, NULL, 8);
	}
	else
	{
		return (-1);
	}

	return (0);
}