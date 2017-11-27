void module_register (void)
{
	plugin_register_log ("myplugin", my_log);
	plugin_register_data_set (&ds);
	plugin_register_read ("myplugin", my_read);
	plugin_register_init ("myplugin", my_init);
	plugin_register_write ("myplugin", my_write);
	plugin_register_shutdown ("myplugin", my_shutdown);
    return;
}