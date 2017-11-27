static void submit_io_time (char const *plugin_instance, derive_t io_time, derive_t weighted_time)
{
	value_t values[2];
	value_list_t vl = VALUE_LIST_INIT;

	if (ignorelist_match (ignorelist, plugin_instance) != 0)
	  return;

	values[0].derive = io_time;
	values[1].derive = weighted_time;

	vl.values = values;
	vl.values_len = 2;
	sstrncpy (vl.host, hostname_g, sizeof (vl.host));
	sstrncpy (vl.plugin, "disk", sizeof (vl.plugin));
	sstrncpy (vl.plugin_instance, plugin_instance, sizeof (vl.plugin_instance));
	sstrncpy (vl.type, "disk_io_time", sizeof (vl.type));

	plugin_dispatch_values (&vl);
}