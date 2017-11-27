static int sl_config (const char *key, const char *value)
{
	if (strcasecmp (key, "LogLevel") == 0)
	{
		if ((strcasecmp (value, "emerg") == 0)
				|| (strcasecmp (value, "alert") == 0)
				|| (strcasecmp (value, "crit") == 0)
				|| (strcasecmp (value, "err") == 0))
			log_level = LOG_ERR;
		else if (strcasecmp (value, "warning") == 0)
			log_level = LOG_WARNING;
		else if (strcasecmp (value, "notice") == 0)
			log_level = LOG_NOTICE;
		else if (strcasecmp (value, "info") == 0)
			log_level = LOG_INFO;
#if COLLECT_DEBUG
		else if (strcasecmp (value, "debug") == 0)
			log_level = LOG_DEBUG;
#endif
		else
			return (1);
	}
	else
		return (-1);

	return (0);
}