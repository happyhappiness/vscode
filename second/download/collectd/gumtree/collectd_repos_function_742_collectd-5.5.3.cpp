static void pf_submit (char const *type, char const *type_instance,
		uint64_t val, _Bool is_gauge)
{
	value_t		values[1];
	value_list_t	vl = VALUE_LIST_INIT;

	if (is_gauge)
		values[0].gauge = (gauge_t) val;
	else
		values[0].derive = (derive_t) val;

	vl.values = values;
	vl.values_len = 1;
	sstrncpy (vl.host, hostname_g, sizeof (vl.host));
	sstrncpy (vl.plugin, "pf", sizeof (vl.plugin));
	sstrncpy (vl.type, type, sizeof(vl.type));
	sstrncpy (vl.type_instance, type_instance, sizeof(vl.type_instance));

	plugin_dispatch_values(&vl);
}