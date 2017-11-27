static int swap_config (oconfig_item_t *ci) /* {{{ */
{
	int i;

	for (i = 0; i < ci->children_num; i++)
	{
		oconfig_item_t *child = ci->children + i;
		if (strcasecmp ("ReportBytes", child->key) == 0)
#if KERNEL_LINUX
			cf_util_get_boolean (child, &report_bytes);
#else
			WARNING ("swap plugin: The \"ReportBytes\" option "
					"is only valid under Linux. "
					"The option is going to be ignored.");
#endif
		else if (strcasecmp ("ReportByDevice", child->key) == 0)
#if SWAP_HAVE_REPORT_BY_DEVICE
			cf_util_get_boolean (child, &report_by_device);
#else
			WARNING ("swap plugin: The \"ReportByDevice\" option "
					"is not supported on this platform. "
					"The option is going to be ignored.");
#endif /* SWAP_HAVE_REPORT_BY_DEVICE */
		else if (strcasecmp ("ValuesAbsolute", child->key) == 0)
			cf_util_get_boolean (child, &values_absolute);
		else if (strcasecmp ("ValuesPercentage", child->key) == 0)
			cf_util_get_boolean (child, &values_percentage);
		else
			WARNING ("swap plugin: Unknown config option: \"%s\"",
					child->key);
	}

	return (0);
}