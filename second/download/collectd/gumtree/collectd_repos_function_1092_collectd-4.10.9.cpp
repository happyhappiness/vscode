void module_register (void)
{
	plugin_register_complex_config ("table", tbl_config);
	plugin_register_init ("table", tbl_init);
}