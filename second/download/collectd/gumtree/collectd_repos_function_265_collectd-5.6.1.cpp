static int varnish_submit (const char *plugin_instance, /* {{{ */
		const char *category, const char *type, const char *type_instance, value_t value)
{
	value_list_t vl = VALUE_LIST_INIT;

	vl.values = &value;
	vl.values_len = 1;

	sstrncpy (vl.host, hostname_g, sizeof (vl.host));

	sstrncpy (vl.plugin, "varnish", sizeof (vl.plugin));

	if (plugin_instance == NULL)
		plugin_instance = "default";

	ssnprintf (vl.plugin_instance, sizeof (vl.plugin_instance),
		"%s-%s", plugin_instance, category);

	sstrncpy (vl.type, type, sizeof (vl.type));

	if (type_instance != NULL)
		sstrncpy (vl.type_instance, type_instance,
				sizeof (vl.type_instance));

	return (plugin_dispatch_values (&vl));
}