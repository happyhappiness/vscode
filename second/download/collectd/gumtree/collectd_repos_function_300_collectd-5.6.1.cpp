static int cpu_config (char const *key, char const *value) /* {{{ */
{
	if (strcasecmp (key, "ReportByCpu") == 0)
		report_by_cpu = IS_TRUE (value) ? 1 : 0;
	else if (strcasecmp (key, "ValuesPercentage") == 0)
		report_percent = IS_TRUE (value) ? 1 : 0;
	else if (strcasecmp (key, "ReportByState") == 0)
		report_by_state = IS_TRUE (value) ? 1 : 0;
	else if (strcasecmp (key, "ReportNumCpu") == 0)
		report_num_cpu = IS_TRUE (value) ? 1 : 0;
	else
		return (-1);

	return (0);
}