void module_register (void)
{
	plugin_register_config ("rrdtool", rrd_config,
			config_keys, config_keys_num);
	plugin_register_init ("rrdtool", rrd_init);
	plugin_register_write ("rrdtool", rrd_write);
	plugin_register_shutdown ("rrdtool", rrd_shutdown);
}