void module_register (void)
{
#if IRQ_HAVE_READ
	plugin_register_config ("irq", irq_config,
			config_keys, config_keys_num);
	plugin_register_read ("irq", irq_read);
#endif /* IRQ_HAVE_READ */
}