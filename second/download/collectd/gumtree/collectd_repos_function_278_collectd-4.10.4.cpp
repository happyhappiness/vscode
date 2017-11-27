static void df_submit_two (char *df_name,
		const char *type,
		gauge_t df_used,
		gauge_t df_free)
{
	value_t values[2];
	value_list_t vl = VALUE_LIST_INIT;

	values[0].gauge = df_used;
	values[1].gauge = df_free;

	vl.values = values;
	vl.values_len = 2;
	sstrncpy (vl.host, hostname_g, sizeof (vl.host));
	sstrncpy (vl.plugin, "df", sizeof (vl.plugin));
	sstrncpy (vl.plugin_instance, "", sizeof (vl.plugin_instance));
	sstrncpy (vl.type, type, sizeof (vl.type));
	sstrncpy (vl.type_instance, df_name, sizeof (vl.type_instance));

	plugin_dispatch_values (&vl);
}