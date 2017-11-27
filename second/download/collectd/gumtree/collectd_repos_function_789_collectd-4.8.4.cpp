static void compression_submit (char *type_instance, gauge_t ratio)
{
	value_t values[1];
	value_list_t vl = VALUE_LIST_INIT;

	values[0].gauge = ratio;

	vl.values = values;
	vl.values_len = STATIC_ARRAY_SIZE (values);
	sstrncpy (vl.host, hostname_g, sizeof (vl.host));
	sstrncpy (vl.plugin, "openvpn", sizeof (vl.plugin));
	sstrncpy (vl.type, "compression_ratio", sizeof (vl.type));
	sstrncpy (vl.type_instance, type_instance, sizeof (vl.type));

	plugin_dispatch_values (&vl);
}