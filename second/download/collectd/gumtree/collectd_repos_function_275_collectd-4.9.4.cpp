static int df_config (const char *key, const char *value)
{
	df_init ();

	if (strcasecmp (key, "Device") == 0)
	{
		if (ignorelist_add (il_device, value))
			return (1);
		return (0);
	}
	else if (strcasecmp (key, "MountPoint") == 0)
	{
		if (ignorelist_add (il_mountpoint, value))
			return (1);
		return (0);
	}
	else if (strcasecmp (key, "FSType") == 0)
	{
		if (ignorelist_add (il_fstype, value))
			return (1);
		return (0);
	}
	else if (strcasecmp (key, "IgnoreSelected") == 0)
	{
		if (IS_TRUE (value))
		{
			ignorelist_set_invert (il_device, 0);
			ignorelist_set_invert (il_mountpoint, 0);
			ignorelist_set_invert (il_fstype, 0);
		}
		else
		{
			ignorelist_set_invert (il_device, 1);
			ignorelist_set_invert (il_mountpoint, 1);
			ignorelist_set_invert (il_fstype, 1);
		}
		return (0);
	}
	else if (strcasecmp (key, "ReportByDevice") == 0)
	{
		if (IS_TRUE (value))
			by_device = true;

		return (0);
	}
	else if (strcasecmp (key, "ReportReserved") == 0)
	{
		if (IS_TRUE (value))
			report_reserved = true;
		else
			report_reserved = false;

		return (0);
	}
	else if (strcasecmp (key, "ReportInodes") == 0)
	{
		if (IS_TRUE (value))
			report_inodes = true;
		else
			report_inodes = false;

		return (0);
	}


	return (-1);
}