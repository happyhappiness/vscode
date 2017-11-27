void module_register (void)
{
	plugin_register_complex_config ("postgresql", c_psql_config);
	plugin_register_shutdown ("postgresql", c_psql_shutdown);
}