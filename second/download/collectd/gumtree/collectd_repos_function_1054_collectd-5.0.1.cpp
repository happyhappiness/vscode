static int swap_config (const char *key, const char *value) /* {{{ */
{
	if (strcasecmp ("ReportByDevice", key) == 0)
	{
		if (IS_TRUE (value))
			report_by_device = 1;
		else
			report_by_device = 0;
	}
	else
	{
		return (-1);
	}

	return (0);
}