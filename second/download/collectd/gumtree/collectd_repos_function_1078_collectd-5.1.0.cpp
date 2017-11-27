static void swap_submit_gauge (const char *plugin_instance, /* {{{ */
		const char *type_instance, gauge_t value)
{
	value_t v;

	v.gauge = value;
	swap_submit (plugin_instance, "swap", type_instance, v);
}