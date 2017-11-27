static int memcached_config (const char *key, const char *value) /* {{{ */
{
	if (strcasecmp (key, "Socket") == 0) {
		if (memcached_socket != NULL) {
			free (memcached_socket);
		}
		memcached_socket = strdup (value);
	} else if (strcasecmp (key, "Host") == 0) {
		if (memcached_host != NULL) {
			free (memcached_host);
		}
		memcached_host = strdup (value);
	} else if (strcasecmp (key, "Port") == 0) {
		int port = (int) (atof (value));
		if ((port > 0) && (port <= 65535)) {
			ssnprintf (memcached_port, sizeof (memcached_port), "%i", port);
		} else {
			sstrncpy (memcached_port, value, sizeof (memcached_port));
		}
	} else {
		return -1;
	}

	return 0;
}