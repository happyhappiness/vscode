	return;

    oom:
	out_of_memory("server_options");
}

/* Look for a HOST specfication of the form "HOST:PATH", "HOST::PATH", or
 * "rsync://HOST:PORT/PATH".  If found, *host_ptr will be set to some allocated
 * memory with the HOST.  If a daemon-accessing spec was specified, the value
 * of *port_ptr will contain a non-0 port number, otherwise it will be set to
 * 0.  The return value is a pointer to the PATH.  Note that the HOST spec can
 * be an IPv6 literal address enclosed in '[' and ']' (such as "[::1]" or
 * "[::ffff:127.0.0.1]") which is returned without the '[' and ']'. */
char *check_for_hostspec(char *s, char **host_ptr, int *port_ptr)
{
	char *p;
	int not_host;
	int hostlen;

	if (port_ptr && strncasecmp(URL_PREFIX, s, strlen(URL_PREFIX)) == 0) {
		char *path;
		s += strlen(URL_PREFIX);
		if ((p = strchr(s, '/')) != NULL) {
			hostlen = p - s;
			path = p + 1;
		} else {
			hostlen = strlen(s);
			path = "";
		}
		if (*s == '[' && (p = strchr(s, ']')) != NULL) {
			s++;
			hostlen = p - s;
			if (p[1] == ':')
				*port_ptr = atoi(p+2);
		} else {
			if ((p = strchr(s, ':')) != NULL && p < s + hostlen) {
				hostlen = p - s;
				*port_ptr = atoi(p+1);
			}
		}
		if (!*port_ptr)
			*port_ptr = RSYNC_PORT;
		*host_ptr = new_array(char, hostlen + 1);
		strlcpy(*host_ptr, s, hostlen + 1);
		return path;
	}

	if (*s == '[' && (p = strchr(s, ']')) != NULL && p[1] == ':') {
		s++;
		hostlen = p - s;
		*p = '\0';
		not_host = strchr(s, '/') || !strchr(s, ':');
		*p = ']';
		if (not_host)
			return NULL;
		p++;
	} else {
		if (!(p = strchr(s, ':')))
			return NULL;
		hostlen = p - s;
		*p = '\0';
		not_host = strchr(s, '/') != NULL;
		*p = ':';
		if (not_host)
			return NULL;
	}

	*host_ptr = new_array(char, hostlen + 1);
	strlcpy(*host_ptr, s, hostlen + 1);

	if (p[1] == ':') {
		if (port_ptr && !*port_ptr)
			*port_ptr = RSYNC_PORT;
		return p + 2;
	}
	if (port_ptr)
		*port_ptr = 0;

	return p + 1;
}
