static void submit_octets (counter_t queries, counter_t responses)
{
	value_t values[2];
	value_list_t vl = VALUE_LIST_INIT;

	values[0].counter = queries;
	values[1].counter = responses;

	vl.values = values;
	vl.values_len = 2;
	vl.time = time (NULL);
	strcpy (vl.host, hostname_g);
	strcpy (vl.plugin, "dns");

	plugin_dispatch_values ("dns_octets", &vl);
}