static void swap_submit (const char *type_instance, derive_t value, unsigned type)
{
	value_t values[1];
	value_list_t vl = VALUE_LIST_INIT;

	switch (type)
	{
		case DS_TYPE_GAUGE:
			values[0].gauge = (gauge_t) value;
			sstrncpy (vl.type, "swap", sizeof (vl.type));
			break;
		case DS_TYPE_DERIVE:
			values[0].derive = value;
			sstrncpy (vl.type, "swap_io", sizeof (vl.type));
			break;
		default:
			ERROR ("swap plugin: swap_submit called with wrong"
				" type");
	}

	vl.values = values;
	vl.values_len = 1;
	sstrncpy (vl.host, hostname_g, sizeof (vl.host));
	sstrncpy (vl.plugin, "swap", sizeof (vl.plugin));
	sstrncpy (vl.type_instance, type_instance, sizeof (vl.type_instance));

	plugin_dispatch_values (&vl);
}