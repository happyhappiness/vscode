static int cna_change_volume_status (const char *hostname, /* {{{ */
		data_volume_usage_t *v)
{
	notification_t n = { 0 };

	n.time = cdtime ();
	sstrncpy (n.host, hostname, sizeof (n.host));
	sstrncpy (n.plugin, "netapp", sizeof (n.plugin));
	sstrncpy (n.plugin_instance, v->name, sizeof (n.plugin_instance));

	if ((v->flags & IS_VOLUME_USAGE_OFFLINE) != 0) {
		n.severity = NOTIF_OKAY;
		ssnprintf (n.message, sizeof (n.message),
				"Volume %s is now online.", v->name);
		v->flags &= ~IS_VOLUME_USAGE_OFFLINE;
	} else {
		n.severity = NOTIF_WARNING;
		ssnprintf (n.message, sizeof (n.message),
				"Volume %s is now offline.", v->name);
		v->flags |= IS_VOLUME_USAGE_OFFLINE;
	}

	return (plugin_dispatch_notification (&n));
}