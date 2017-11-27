static char *get_device_name(const char *optstr)
{
	char *rc;

	if (optstr == NULL)
	{
		return (NULL);
	}
	else if (strncmp (optstr, "UUID=", 5) == 0)
	{
		DEBUG ("utils_mount: TODO: check UUID= code!");
		rc = get_spec_by_uuid (optstr + 5);
	}
	else if (strncmp (optstr, "LABEL=", 6) == 0)
	{
		DEBUG ("utils_mount: TODO: check LABEL= code!");
		rc = get_spec_by_volume_label (optstr + 6);
	}
	else
	{
		rc = sstrdup (optstr);
	}

	if(!rc)
	{
		DEBUG ("utils_mount: Error checking device name: optstr = %s", optstr);
	}
	return rc;
}