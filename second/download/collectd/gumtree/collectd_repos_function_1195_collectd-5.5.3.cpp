static void cldap_submit_value (const char *type, const char *type_instance, /* {{{ */
		value_t value, cldap_t *st)
{
	value_list_t vl = VALUE_LIST_INIT;

	vl.values     = &value;
	vl.values_len = 1;

	if ((st->host == NULL)
			|| (strcmp ("", st->host) == 0)
			|| (strcmp ("localhost", st->host) == 0))
	{
		sstrncpy (vl.host, hostname_g, sizeof (vl.host));
	}
	else
	{
		sstrncpy (vl.host, st->host, sizeof (vl.host));
	}

	sstrncpy (vl.plugin, "openldap", sizeof (vl.plugin));
	if (st->name != NULL)
		sstrncpy (vl.plugin_instance, st->name,
				sizeof (vl.plugin_instance));

	sstrncpy (vl.type, type, sizeof (vl.type));
	if (type_instance != NULL)
		sstrncpy (vl.type_instance, type_instance,
				sizeof (vl.type_instance));

	plugin_dispatch_values (&vl);
}