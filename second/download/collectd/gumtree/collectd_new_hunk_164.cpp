
#if COLLECT_DEBUG
	assert (ds->ds_num == vl->values_len);
#else
	if (ds->ds_num != vl->values_len)
	{
		ERROR ("plugin: ds->type = %s: (ds->ds_num = %i) != "
				"(vl->values_len = %i)",
				ds->type, ds->ds_num, vl->values_len);
		return (-1);
	}
#endif

	escape_slashes (vl->host, sizeof (vl->host));
	escape_slashes (vl->plugin, sizeof (vl->plugin));
	escape_slashes (vl->plugin_instance, sizeof (vl->plugin_instance));
	escape_slashes (vl->type_instance, sizeof (vl->type_instance));

	/* Update the value cache */
	uc_update (ds, vl);
	ut_check_threshold (ds, vl);

	le = llist_head (list_write);
	while (le != NULL)
	{
		callback = (int (*) (const data_set_t *, const value_list_t *)) le->value;
		(*callback) (ds, vl);

		le = le->next;
	}

	return (0);
} /* int plugin_dispatch_values */

int plugin_dispatch_notification (const notification_t *notif)
{
	int (*callback) (const notification_t *);
	llentry_t *le;
	/* Possible TODO: Add flap detection here */

	DEBUG ("plugin_dispatch_notification: severity = %i; message = %s; "
			"time = %u; host = %s;",
			notif->severity, notif->message,
			(unsigned int) notif->time, notif->host);

	/* Nobody cares for notifications */
	if (list_notification == NULL)
		return (-1);

	le = llist_head (list_notification);
	while (le != NULL)
	{
		callback = (int (*) (const notification_t *)) le->value;
		(*callback) (notif);

		le = le->next;
	}

	return (0);
} /* int plugin_dispatch_notification */

void plugin_log (int level, const char *format, ...)
{
	char msg[512];
	va_list ap;

	void (*callback) (int, const char *);
