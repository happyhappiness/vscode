void
module_register (void)
{
    plugin_register_config ("libvirt",
	    lv_config,
	    config_keys, NR_CONFIG_KEYS);
    plugin_register_init ("libvirt", lv_init);
    plugin_register_read ("libvirt", lv_read);
    plugin_register_shutdown ("libvirt", lv_shutdown);
}