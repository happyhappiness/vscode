void module_register (void)
{
	plugin_register_read ("serial", serial_read);
}