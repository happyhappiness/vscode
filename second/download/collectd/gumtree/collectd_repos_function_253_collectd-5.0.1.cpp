void module_register (void) /* {{{ */
{
	plugin_register_complex_config ("varnish", varnish_config);
	plugin_register_init ("varnish", varnish_init);
}