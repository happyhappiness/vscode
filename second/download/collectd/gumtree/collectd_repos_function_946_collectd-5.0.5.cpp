void module_register(void) {
	plugin_register_complex_config("netapp", cna_config);
	plugin_register_init("netapp", cna_init);
	plugin_register_shutdown("netapp", cna_shutdown);
}