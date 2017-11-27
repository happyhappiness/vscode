static int mbmon_read (void)
{
	char buf[1024];
	char *s, *t;

	/* get data from daemon */
	if (mbmon_query_daemon (buf, sizeof (buf)) < 0)
		return (-1);

	s = buf;
	while ((t = strchr (s, ':')) != NULL)
	{
		double value;
		char *nextc;

		char *type;
		char *inst;

		*t++ = '\0';
		trim_spaces (s);

		value = strtod (t, &nextc);
		if ((*nextc != '\n') && (*nextc != '\0'))
		{
			ERROR ("mbmon: value for `%s' contains invalid characters: `%s'", s, t);
			break;
		}

		if (strncmp (s, "TEMP", 4) == 0)
		{
			inst = s + 4;
			type = "temperature";
		}
		else if (strncmp (s, "FAN", 3) == 0)
		{
			inst = s + 3;
			type = "fanspeed";
		}
		else if (strncmp (s, "V", 1) == 0)
		{
			inst = s + 1;
			type = "voltage";
		}
		else
		{
			continue;
		}

		mbmon_submit (type, inst, value);

		if (*nextc == '\0')
			break;

		s = nextc + 1;
	}

	return (0);
}