	return;

    oom:
	out_of_memory("server_options");
}

/* If str points to a valid hostspec, return allocated memory containing the
 * [USER@]HOST part of the string, and set the path_start_ptr to the part of
 * the string after the host part.  Otherwise, return NULL.  If port_ptr is
 * non-NULL, we must be parsing an rsync:// URL hostname, and we will set
 * *port_ptr if a port number is found.  Note that IPv6 IPs will have their
 * (required for parsing) [ and ] chars elided from the returned string. */
static char *parse_hostspec(char *str, char **path_start_ptr, int *port_ptr)
{
	char *s, *host_start = str;
	int hostlen = 0, userlen = 0;
	char *ret;

	for (s = str; ; s++) {
		if (!*s) {
			/* It is only OK if we run out of string with rsync:// */
			if (!port_ptr)
				return NULL;
			if (!hostlen)
				hostlen = s - host_start;
			break;
		}
		if (*s == ':' || *s == '/') {
			if (!hostlen)
				hostlen = s - host_start;
			if (*s++ == '/') {
				if (!port_ptr)
					return NULL;
			} else if (port_ptr) {
				*port_ptr = atoi(s);
				while (isDigit(s)) s++;
				if (*s && *s++ != '/')
					return NULL;
			}
			break;
		}
		if (*s == '@') {
			userlen = s - str + 1;
			host_start = s + 1;
		} else if (*s == '[') {
			if (s != host_start++)
				return NULL;
			while (*s && *s != ']' && *s != '/') s++; /*SHARED ITERATOR*/
			hostlen = s - host_start;
			if (*s != ']' || (s[1] && s[1] != '/' && s[1] != ':') || !hostlen)
				return NULL;
		}
	}

	*path_start_ptr = s;
	ret = new_array(char, userlen + hostlen + 1);
	if (userlen)
		strlcpy(ret, str, userlen + 1);
	strlcpy(ret + userlen, host_start, hostlen + 1);
	return ret;
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
	char *path;

	if (port_ptr && strncasecmp(URL_PREFIX, s, strlen(URL_PREFIX)) == 0) {
		*host_ptr = parse_hostspec(s + strlen(URL_PREFIX), &path, port_ptr);
		if (*host_ptr) {
			if (!*port_ptr)
				*port_ptr = RSYNC_PORT;
			return path;
		}
	}

	*host_ptr = parse_hostspec(s, &path, NULL);
	if (!*host_ptr)
		return NULL;

	if (*path == ':') {
		if (port_ptr && !*port_ptr)
			*port_ptr = RSYNC_PORT;
		return path + 1;
	}
	if (port_ptr)
		*port_ptr = 0;

	return path;
}
