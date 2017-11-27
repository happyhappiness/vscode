static void entropy_submit (double entropy)
{
	value_t values[1];
	value_list_t vl = VALUE_LIST_INIT;

	values[0].gauge = entropy;

	vl.values = values;
	vl.values_len = 1;
	vl.time = time (NULL);
	sstrncpy (vl.host, hostname_g, sizeof (vl.host));
	sstrncpy (vl.plugin, "entropy", sizeof (vl.plugin));
	sstrncpy (vl.plugin_instance, "", sizeof (vl.plugin_instance));
	sstrncpy (vl.type_instance, "", sizeof (vl.type_instance));

	plugin_dispatch_values ("entropy", &vl);
}