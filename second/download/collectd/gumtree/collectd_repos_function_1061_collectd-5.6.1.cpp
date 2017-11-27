static void numusers_submit (const char *pinst, const char *tinst,
		gauge_t value)
{
	value_t values[1];
	value_list_t vl = VALUE_LIST_INIT;

	values[0].gauge = value;

	vl.values = values;
	vl.values_len = STATIC_ARRAY_SIZE (values);
	sstrncpy (vl.host, hostname_g, sizeof (vl.host));
	sstrncpy (vl.plugin, "openvpn", sizeof (vl.plugin));
	sstrncpy (vl.type, "users", sizeof (vl.type));
	if (pinst != NULL)
		sstrncpy (vl.plugin_instance, pinst, sizeof (vl.plugin_instance));
	if (tinst != NULL)
		sstrncpy (vl.type_instance, tinst, sizeof (vl.type_instance));

	plugin_dispatch_values (&vl);
}