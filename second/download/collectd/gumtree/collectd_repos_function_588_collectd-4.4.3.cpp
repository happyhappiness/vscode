static void as_submit (const char *type, const char *type_instance,
		double val)
{
	value_t values[1];
	value_list_t vl = VALUE_LIST_INIT;

	DEBUG ("type = %s; type_instance = %s; val = %f;",
			type, type_instance, val);

	values[0].gauge = val;

	vl.values = values;
	vl.values_len = 1;
	vl.time = time (NULL);
	sstrncpy (vl.host, hostname_g, sizeof (vl.host));
	sstrncpy (vl.plugin, "apple_sensors", sizeof (vl.plugin));
	sstrncpy (vl.plugin_instance, "", sizeof (vl.plugin_instance));
	sstrncpy (vl.type_instance, type_instance, sizeof (vl.type_instance));

	plugin_dispatch_values (type, &vl);
}