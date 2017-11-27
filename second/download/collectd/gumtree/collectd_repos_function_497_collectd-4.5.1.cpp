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
		sstrncpy (n.message, SvPV_nolen (*tmp), sizeof (n.message));

	if (NULL != (tmp = hv_fetch (notif, "host", 4, 0)))
		sstrncpy (n.host, SvPV_nolen (*tmp), sizeof (n.host));
	else
		sstrncpy (n.host, hostname_g, sizeof (n.host));

	if (NULL != (tmp = hv_fetch (notif, "plugin", 6, 0)))
		sstrncpy (n.plugin, SvPV_nolen (*tmp), sizeof (n.plugin));

	if (NULL != (tmp = hv_fetch (notif, "plugin_instance", 15, 0)))
		sstrncpy (n.plugin_instance, SvPV_nolen (*tmp),
				sizeof (n.plugin_instance));

	if (NULL != (tmp = hv_fetch (notif, "type", 4, 0)))
		sstrncpy (n.type, SvPV_nolen (*tmp), sizeof (n.type));

	if (NULL != (tmp = hv_fetch (notif, "type_instance", 13, 0)))
		sstrncpy (n.type_instance, SvPV_nolen (*tmp), sizeof (n.type_instance));
	return plugin_dispatch_notification (&n);
}