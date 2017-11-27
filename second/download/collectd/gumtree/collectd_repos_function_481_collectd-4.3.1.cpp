static void entropy_submit (double entropy)
{
	value_t values[1];
	value_list_t vl = VALUE_LIST_INIT;

	values[0].gauge = entropy;

	vl.values = values;
	vl.values_len = 1;
	vl.time = time (NULL);
	strcpy (vl.host, hostname_g);
	strcpy (vl.plugin, "entropy");
	strcpy (vl.plugin_instance, "");
	strcpy (vl.type_instance, "");

	plugin_dispatch_values ("entropy", &vl);
}