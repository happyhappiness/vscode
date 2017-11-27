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
	else if (strcasecmp (key, "socket") == 0)
		return ((socket = strdup (value)) == NULL ? 1 : 0);
	else if (strcasecmp (key, "port") == 0)
	{
	    char *endptr = NULL;
	    int temp;

	    errno = 0;
	    temp = strtol (value, &endptr, 0);
	    if ((errno != 0) || (value == endptr))
	    {
		ERROR ("mysql plugin: Invalid \"Port\" argument: %s",
			value);
		port = 0;
		return (1);
	    }
	    else if ((temp < 0) || (temp >= 65535))
	    {
		ERROR ("mysql plugin: Port number out of range: %i",
			temp);
		port = 0;
		return (1);
	    }

	    port = temp;
	    return (0);
	}
	else
		return (-1);
}