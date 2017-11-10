static unsigned int get_index_format_default(void)
{
	char *envversion = getenv("GIT_INDEX_VERSION");
	char *endp;
	int value;
	unsigned int version = INDEX_FORMAT_DEFAULT;

	if (!envversion) {
		if (!git_config_get_int("index.version", &value))
			version = value;
		if (version < INDEX_FORMAT_LB || INDEX_FORMAT_UB < version) {
			warning(_("index.version set, but the value is invalid.\n"
				  "Using version %i"), INDEX_FORMAT_DEFAULT);
			return INDEX_FORMAT_DEFAULT;
		}
		return version;
	}

	version = strtoul(envversion, &endp, 10);
	if (*endp ||
	    version < INDEX_FORMAT_LB || INDEX_FORMAT_UB < version) {
		warning(_("GIT_INDEX_VERSION set, but the value is invalid.\n"
			  "Using version %i"), INDEX_FORMAT_DEFAULT);
		version = INDEX_FORMAT_DEFAULT;
	}
	return version;
}