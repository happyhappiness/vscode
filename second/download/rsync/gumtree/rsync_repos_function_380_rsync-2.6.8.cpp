char *check_for_hostspec(char *s, char **host_ptr, int *port_ptr)
{
	char *p;
	int not_host;

	if (port_ptr && strncasecmp(URL_PREFIX, s, strlen(URL_PREFIX)) == 0) {
		char *path;
		int hostlen;
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
			if ((p = strchr(s, ':')) != NULL) {
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
		*p = '\0';
		not_host = strchr(s, '/') || !strchr(s, ':');
		*p = ']';
		if (not_host)
			return NULL;
		p++;
	} else {
		if (!(p = strchr(s, ':')))
			return NULL;
		*p = '\0';
		not_host = strchr(s, '/') != NULL;
		*p = ':';
		if (not_host)
			return NULL;
	}

	*host_ptr = new_array(char, p - s + 1);
	strlcpy(*host_ptr, s, p - s + 1);

	if (p[1] == ':') {
		if (port_ptr && !*port_ptr)
			*port_ptr = RSYNC_PORT;
		return p + 2;
	}
	if (port_ptr)
		*port_ptr = 0;

	return p + 1;
}