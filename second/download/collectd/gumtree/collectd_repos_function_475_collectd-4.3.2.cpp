static int logfile_notification (const notification_t *n)
{
	char  buf[1024] = "";
	char *buf_ptr = buf;
	int   buf_len = sizeof (buf);
	int status;

	status = snprintf (buf_ptr, buf_len, "Notification: severity = %s",
			(n->severity == NOTIF_FAILURE) ? "FAILURE"
			: ((n->severity == NOTIF_WARNING) ? "WARNING"
				: ((n->severity == NOTIF_OKAY) ? "OKAY" : "UNKNOWN")));
	if (status > 0)
	{
		buf_ptr += status;
		buf_len -= status;
	}

#define APPEND(bufptr, buflen, key, value) \
	if ((buflen > 0) && (strlen (value) > 0)) { \
		int status = snprintf (bufptr, buflen, ", %s = %s", key, value); \
		if (status > 0) { \
			bufptr += status; \
			buflen -= status; \
		} \
	}
	APPEND (buf_ptr, buf_len, "host", n->host);
	APPEND (buf_ptr, buf_len, "plugin", n->plugin);
	APPEND (buf_ptr, buf_len, "plugin_instance", n->plugin_instance);
	APPEND (buf_ptr, buf_len, "type", n->type);
	APPEND (buf_ptr, buf_len, "type_instance", n->type_instance);
	APPEND (buf_ptr, buf_len, "message", n->message);

	buf[sizeof (buf) - 1] = '\0';

	logfile_print (buf, n->time);

	return (0);
}