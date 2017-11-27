static void submit_counter2 (const char *type, const char *type_inst,
		counter_t value0, counter_t value1) /* {{{ */
{
	value_t values[2];
	value_list_t vl = VALUE_LIST_INIT;

	values[0].counter = value0;
	values[1].counter = value1;

	vl.values = values;
	vl.values_len = 2;
	vl.time = time (NULL);
	strcpy (vl.host, hostname_g);
	strcpy (vl.plugin, "memcached");
	if (type_inst != NULL)
	{
		strncpy (vl.type_instance, type_inst, sizeof (vl.type_instance));
		vl.type_instance[sizeof (vl.type_instance) - 1] = '\0';
	}

	plugin_dispatch_values (type, &vl);
}