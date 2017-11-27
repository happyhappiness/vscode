static int varnish_submit_derive (const char *plugin_instance, /* {{{ */
		const char *category, const char *type, const char *type_instance,
		uint64_t derive_value)
{
	value_t value;

	value.derive = (derive_t) derive_value;

	return (varnish_submit (plugin_instance, category, type, type_instance, value));
}