static int dns_config (const char *key, const char *value)
{
	if (strcasecmp (key, "Interface") == 0)
	{
		if (pcap_device != NULL)
			free (pcap_device);
		if ((pcap_device = strdup (value)) == NULL)
			return (1);
	}
	else if (strcasecmp (key, "IgnoreSource") == 0)
	{
		if (value != NULL)
			ignore_list_add_name (value);
	}
	else
	{
		return (-1);
	}

	return (0);
}