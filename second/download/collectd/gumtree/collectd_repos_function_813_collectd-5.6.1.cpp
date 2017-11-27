static int log_logstash_config (const char *key, const char *value)
{

	if (0 == strcasecmp (key, "LogLevel")) {
		log_level = parse_log_severity(value);
		if (log_level < 0) {
			log_level = LOG_INFO;
			ERROR("log_logstash: invalid loglevel [%s] defaulting to 'info'",
				value);
			return 1;
		}
	}
	else if (0 == strcasecmp (key, "File")) {
		sfree (log_file);
		log_file = strdup (value);
	}
	else {
		return -1;
	}
	return 0;
}