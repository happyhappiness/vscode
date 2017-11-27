static int submit_two_counters (const char *host, const char *plugin_inst, /* {{{ */
		const char *type, const char *type_inst, counter_t val0, counter_t val1,
		time_t timestamp)
{
	value_t values[2];

	values[0].counter = val0;
	values[1].counter = val1;

	return (submit_values (host, plugin_inst, type, type_inst,
				values, 2, timestamp));
}