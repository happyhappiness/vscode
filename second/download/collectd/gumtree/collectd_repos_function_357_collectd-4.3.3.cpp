static int memcached_config (const char *key, const char *value) /* {{{ */
{
	if (strcasecmp (key, "Host") == 0) {
		if (memcached_host != NULL) {
			free (memcached_host);
		}
		memcached_host = strdup (value);
	} else if (strcasecmp (key, "Port") == 0) {
		int port = (int) (atof (value));
		if ((port > 0) && (port <= 65535)) {
			snprintf (memcached_port, sizeof (memcached_port), "%i", port);
		} else {
			strncpy (memcached_port, value, sizeof (memcached_port));
		}
		memcached_port[sizeof (memcached_port) - 1] = '\0';
	} else {
		return -1;
	}

	return 0;
}