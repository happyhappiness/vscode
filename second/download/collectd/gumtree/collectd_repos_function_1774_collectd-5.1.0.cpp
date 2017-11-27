int parse_notif_severity (const char *severity)
{
	int notif_severity = -1;

	if (strcasecmp (severity, "FAILURE") == 0)
		notif_severity = NOTIF_FAILURE;
	else if (strcmp (severity, "OKAY") == 0)
		notif_severity = NOTIF_OKAY;
	else if ((strcmp (severity, "WARNING") == 0)
			|| (strcmp (severity, "WARN") == 0))
		notif_severity = NOTIF_WARNING;

	return (notif_severity);
}