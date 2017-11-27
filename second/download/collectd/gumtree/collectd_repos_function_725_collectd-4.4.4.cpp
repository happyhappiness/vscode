static int config (const char *key, const char *value)
{
	if (strcasecmp (key, "host") == 0)
		return ((host = strdup (value)) == NULL ? 1 : 0);
	else if (strcasecmp (key, "user") == 0)
		return ((user = strdup (value)) == NULL ? 1 : 0);
	else if (strcasecmp (key, "password") == 0)
		return ((pass = strdup (value)) == NULL ? 1 : 0);
	else if (strcasecmp (key, "database") == 0)
		return ((db = strdup (value)) == NULL ? 1 : 0);
	else
		return (-1);
}