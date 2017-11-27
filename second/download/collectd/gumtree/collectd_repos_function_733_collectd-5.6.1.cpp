void module_register (void)
{
    plugin_register_config ("iptables", iptables_config,
                             config_keys, config_keys_num);
    plugin_register_init ("iptables", iptables_init);
    plugin_register_read ("iptables", iptables_read);
    plugin_register_shutdown ("iptables", iptables_shutdown);
}