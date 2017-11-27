void module_register(void)
{
	plugin_register_complex_config ("write_riemann", riemann_config);
}