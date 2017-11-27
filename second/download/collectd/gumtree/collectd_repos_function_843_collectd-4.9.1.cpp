static int submit_two_gauge (const char *host, const char *plugin_inst, /* {{{ */
		const char *type, const char *type_inst, gauge_t val0, gauge_t val1,
		time_t timestamp)
{
	value_t values[2];

	values[0].gauge = val0;
	values[1].gauge = val1;

	return (submit_values (host, plugin_inst, type, type_inst,
				values, 2, timestamp));
}