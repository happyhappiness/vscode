const char *current_config_origin_type(void)
{
	int type;
	if (current_config_kvi)
		type = current_config_kvi->origin_type;
	else if(cf)
		type = cf->origin_type;
	else
		die("BUG: current_config_origin_type called outside config callback");

	switch (type) {
	case CONFIG_ORIGIN_BLOB:
		return "blob";
	case CONFIG_ORIGIN_FILE:
		return "file";
	case CONFIG_ORIGIN_STDIN:
		return "standard input";
	case CONFIG_ORIGIN_SUBMODULE_BLOB:
		return "submodule-blob";
	case CONFIG_ORIGIN_CMDLINE:
		return "command line";
	default:
		die("BUG: unknown config origin type");
	}
}