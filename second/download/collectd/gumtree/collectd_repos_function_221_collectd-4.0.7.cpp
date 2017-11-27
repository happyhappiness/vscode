static int ps_config (const char *key, const char *value)
{
	if (strcasecmp (key, "Process") == 0)
	{
		ps_list_register (value);
	}
	else
	{
		return (-1);
	}

	return (0);
}