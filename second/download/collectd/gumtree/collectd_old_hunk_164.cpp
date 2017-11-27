
#if COLLECT_DEBUG
	assert (ds->ds_num == vl->values_len);
#else
	if (ds->ds_num != vl->values_len)
	{
		ERROR ("plugin_dispatch_values: ds->type = %s: "
				"(ds->ds_num = %i) != "
				"(vl->values_len = %i)",
				ds->type, ds->ds_num, vl->values_len);
		return (-1);
	}
#endif

	escape_slashes (vl->host, sizeof (vl->host));
	escape_slashes (vl->plugin, sizeof (vl->plugin));
	escape_slashes (vl->plugin_instance, sizeof (vl->plugin_instance));
	escape_slashes (vl->type_instance, sizeof (vl->type_instance));

	le = llist_head (list_write);
	while (le != NULL)
	{
		callback = (int (*) (const data_set_t *, const value_list_t *)) le->value;
		(*callback) (ds, vl);

		le = le->next;
	}

	return (0);
} /* int plugin_dispatch_values */

void plugin_log (int level, const char *format, ...)
{
	char msg[512];
	va_list ap;

	void (*callback) (int, const char *);
