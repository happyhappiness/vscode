static int host_matches(const char *host, const char *pattern)
{
	if (pattern[0] == '*' && pattern[1] == '.') {
		pattern += 2;
		if (!(host = strchr(host, '.')))
			return 0;
		host++;
	}

	return *host && *pattern && !strcasecmp(host, pattern);
}