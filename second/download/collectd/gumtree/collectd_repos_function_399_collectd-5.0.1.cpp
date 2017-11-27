static void if_submit (const char *dev, const char *type,
		derive_t rx,
		derive_t tx)
{
	value_t values[2];
	value_list_t vl = VALUE_LIST_INIT;

	if (ignorelist_match (ignorelist, dev) != 0)
		return;

	values[0].derive = rx;
	values[1].derive = tx;

	vl.values = values;
	vl.values_len = 2;
	sstrncpy (vl.host, hostname_g, sizeof (vl.host));
	sstrncpy (vl.plugin, "interface", sizeof (vl.plugin));
	sstrncpy (vl.plugin_instance, dev, sizeof (vl.plugin_instance));
	sstrncpy (vl.type, type, sizeof (vl.type));

	plugin_dispatch_values (&vl);
}