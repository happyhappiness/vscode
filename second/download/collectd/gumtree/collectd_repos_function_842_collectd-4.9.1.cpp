static int submit_counter (const char *host, const char *plugin_inst, /* {{{ */
		const char *type, const char *type_inst, counter_t counter, time_t timestamp)
{
	value_t v;

	v.counter = counter;

	return (submit_values (host, plugin_inst, type, type_inst,
				&v, 1, timestamp));
}