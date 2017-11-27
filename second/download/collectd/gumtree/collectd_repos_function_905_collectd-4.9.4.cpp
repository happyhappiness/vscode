static int logfile_config (const char *key, const char *value)
{
	if (0 == strcasecmp (key, "LogLevel")) {
		if ((0 == strcasecmp (value, "emerg"))
				|| (0 == strcasecmp (value, "alert"))
				|| (0 == strcasecmp (value, "crit"))
				|| (0 == strcasecmp (value, "err")))
			log_level = LOG_ERR;
		else if (0 == strcasecmp (value, "warning"))
			log_level = LOG_WARNING;
		else if (0 == strcasecmp (value, "notice"))
			log_level = LOG_NOTICE;
		else if (0 == strcasecmp (value, "info"))
			log_level = LOG_INFO;
#if COLLECT_DEBUG
		else if (0 == strcasecmp (value, "debug"))
			log_level = LOG_DEBUG;
#endif /* COLLECT_DEBUG */
		else
			return 1;
	}
	else if (0 == strcasecmp (key, "File")) {
		sfree (log_file);
		log_file = strdup (value);
	}
	else if (0 == strcasecmp (key, "Timestamp")) {
		if (IS_FALSE (value))
			print_timestamp = 0;
		else
			print_timestamp = 1;
	}
	else {
		return -1;
	}
	return 0;
}