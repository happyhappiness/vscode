void module_register (void) /* {{{ */
{
	plugin_register_complex_config ("openldap", cldap_config);
	plugin_register_init ("openldap", cldap_init);
	plugin_register_shutdown ("openldap", cldap_shutdown);
}