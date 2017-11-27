static int openvpn_config (const char *key, const char *value)
{
	if (strcasecmp ("StatusFile", key) == 0)
	{
		sfree (status_file);
		status_file = sstrdup (value);
	}
	else
	{
		return (-1);
	}
        return (0);
}