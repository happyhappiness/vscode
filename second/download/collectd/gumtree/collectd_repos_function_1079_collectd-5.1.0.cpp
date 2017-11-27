static void swap_submit_derive (const char *plugin_instance, /* {{{ */
		const char *type_instance, derive_t value)
{
	value_t v;

	v.derive = value;
	swap_submit (plugin_instance, "swap_io", type_instance, v);
}