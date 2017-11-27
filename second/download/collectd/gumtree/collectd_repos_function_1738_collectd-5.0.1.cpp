static void cipvs_submit_if (char *pi, char *t, char *ti,
		derive_t rx, derive_t tx)
{
	value_t values[2];
	value_list_t vl = VALUE_LIST_INIT;

	values[0].derive = rx;
	values[1].derive = tx;

	vl.values     = values;
	vl.values_len = 2;

	sstrncpy (vl.host, hostname_g, sizeof (vl.host));
	sstrncpy (vl.plugin, "ipvs", sizeof (vl.plugin));
	sstrncpy (vl.plugin_instance, pi, sizeof (vl.plugin_instance));
	sstrncpy (vl.type, t, sizeof (vl.type));
	sstrncpy (vl.type_instance, (NULL != ti) ? ti : "total",
		sizeof (vl.type_instance));

	plugin_dispatch_values (&vl);
	return;
}