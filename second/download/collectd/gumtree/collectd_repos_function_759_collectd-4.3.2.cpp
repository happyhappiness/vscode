static void cipvs_submit_if (char *pi, char *t, char *ti,
		counter_t rx, counter_t tx)
{
	value_t values[2];
	value_list_t vl = VALUE_LIST_INIT;

	values[0].counter = rx;
	values[1].counter = tx;

	vl.values     = values;
	vl.values_len = 2;

	vl.time     = time (NULL);
	vl.interval = interval_g;

	strcpy (vl.host, hostname_g);
	strcpy (vl.plugin, "ipvs");
	strcpy (vl.plugin_instance, pi);
	strcpy (vl.type_instance, (NULL != ti) ? ti : "total");

	plugin_dispatch_values (t, &vl);
	return;
}