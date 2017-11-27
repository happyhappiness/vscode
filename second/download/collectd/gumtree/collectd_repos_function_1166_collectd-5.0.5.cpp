static int lpar_config (const char *key, const char *value)
{
	if (strcasecmp ("CpuPoolStats", key) == 0)
	{
		if (IS_TRUE (value))
			pool_stats = 1;
		else
			pool_stats = 0;
	}
	else if (strcasecmp ("ReportBySerial", key) == 0)
	{
		if (IS_TRUE (value))
			report_by_serial = 1;
		else
			report_by_serial = 0;
	}
	else
	{
		return (-1);
	}

	return (0);
}