static void if_submit (const char *dev, const char *type,
		unsigned long long rx,
		unsigned long long tx)
{
	value_t values[2];
	value_list_t vl = VALUE_LIST_INIT;

	if (ignorelist_match (ignorelist, dev) != 0)
		return;

	values[0].counter = rx;
	values[1].counter = tx;

	vl.values = values;
	vl.values_len = 2;
	sstrncpy (vl.host, hostname_g, sizeof (vl.host));
	sstrncpy (vl.plugin, "interface", sizeof (vl.plugin));
	sstrncpy (vl.type, type, sizeof (vl.type));
	sstrncpy (vl.type_instance, dev, sizeof (vl.type_instance));

	plugin_dispatch_values (&vl);
}