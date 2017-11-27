static int submit_double (const char *host, const char *plugin_inst, /* {{{ */
		const char *type, const char *type_inst, double d, time_t timestamp, int interval)
{
	value_t v;

	v.gauge = (gauge_t) d;

	return (submit_values (host, plugin_inst, type, type_inst,
				&v, 1, timestamp, interval));
}