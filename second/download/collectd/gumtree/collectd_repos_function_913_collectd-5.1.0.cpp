static int submit_two_derive (const char *host, const char *plugin_inst, /* {{{ */
		const char *type, const char *type_inst, derive_t val0, derive_t val1,
		cdtime_t timestamp, cdtime_t interval)
{
	value_t values[2];

	values[0].derive = val0;
	values[1].derive = val1;

	return (submit_values (host, plugin_inst, type, type_inst,
				values, 2, timestamp, interval));
}