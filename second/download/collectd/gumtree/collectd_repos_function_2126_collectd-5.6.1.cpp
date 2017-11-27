void module_register (void)
{
	plugin_register_complex_config ("aquaero", aquaero_config);
	plugin_register_read ("aquaero", aquaero_read);
	plugin_register_shutdown ("aquaero", aquaero_shutdown);
}