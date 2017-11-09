static void check_argc(int argc, int min, int max) {
	if (argc >= min && argc <= max)
		return;
	error("wrong number of arguments");
	usage_with_options(builtin_config_usage, builtin_config_options);
}