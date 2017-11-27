static int pplugin_dispatch_notification (pTHX_ HV *notif)
{
	notification_t n;

	SV **tmp = NULL;

	if (NULL == notif)
		return -1;

	memset (&n, 0, sizeof (n));

	if (NULL != (tmp = hv_fetch (notif, "severity", 8, 0)))
		n.severity = SvIV (*tmp);
	else
		n.severity = NOTIF_FAILURE;

	if (NULL != (tmp = hv_fetch (notif, "time", 4, 0)))
		n.time = (time_t)SvIV (*tmp);
	else
		n.time = time (NULL);

	if (NULL != (tmp = hv_fetch (notif, "message", 7, 0)))
		strncpy (n.message, SvPV_nolen (*tmp), sizeof (n.message));
	n.message[sizeof (n.message) - 1] = '\0';

	if (NULL != (tmp = hv_fetch (notif, "host", 4, 0)))
		strncpy (n.host, SvPV_nolen (*tmp), sizeof (n.host));
	else
		strncpy (n.host, hostname_g, sizeof (n.host));
	n.host[sizeof (n.host) - 1] = '\0';

	if (NULL != (tmp = hv_fetch (notif, "plugin", 6, 0)))
		strncpy (n.plugin, SvPV_nolen (*tmp), sizeof (n.plugin));
	n.plugin[sizeof (n.plugin) - 1] = '\0';

	if (NULL != (tmp = hv_fetch (notif, "plugin_instance", 15, 0)))
		strncpy (n.plugin_instance, SvPV_nolen (*tmp),
				sizeof (n.plugin_instance));
	n.plugin_instance[sizeof (n.plugin_instance) - 1] = '\0';

	if (NULL != (tmp = hv_fetch (notif, "type", 4, 0)))
		strncpy (n.type, SvPV_nolen (*tmp), sizeof (n.type));
	n.type[sizeof (n.type) - 1] = '\0';

	if (NULL != (tmp = hv_fetch (notif, "type_instance", 13, 0)))
		strncpy (n.type_instance, SvPV_nolen (*tmp), sizeof (n.type_instance));
	n.type_instance[sizeof (n.type_instance) - 1] = '\0';
	return plugin_dispatch_notification (&n);
}