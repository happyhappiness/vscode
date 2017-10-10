
	return 0;
}

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

const char *current_config_name(void)
{
	const char *name;
	if (current_config_kvi)
		name = current_config_kvi->filename;
	else if (cf)
		name = cf->name;
	else
		die("BUG: current_config_name called outside config callback");
	return name ? name : "";
}

enum config_scope current_config_scope(void)
{
	if (current_config_kvi)
		return current_config_kvi->scope;
	else
		return current_parsing_scope;
}
