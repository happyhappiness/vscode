static void conntrack_submit (const char *type, const char *type_instance,
			      value_t conntrack)
{
	value_list_t vl = VALUE_LIST_INIT;

	vl.values = &conntrack;
	vl.values_len = 1;
	sstrncpy (vl.host, hostname_g, sizeof (vl.host));
	sstrncpy (vl.plugin, "conntrack", sizeof (vl.plugin));
	sstrncpy (vl.type, type, sizeof (vl.type));
	if (type_instance != NULL)
		sstrncpy (vl.type_instance, type_instance,
			  sizeof (vl.type_instance));

	plugin_dispatch_values (&vl);
}