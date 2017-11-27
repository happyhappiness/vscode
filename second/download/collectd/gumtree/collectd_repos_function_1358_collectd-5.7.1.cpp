void module_register(void)
	{
		plugin_register_complex_config("grpc", c_grpc_config);
		plugin_register_init("grpc", c_grpc_init);
		plugin_register_shutdown("grpc", c_grpc_shutdown);
	}