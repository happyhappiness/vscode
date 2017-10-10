	die("This version of fast-import does not support option: %s", option);
}

static void git_pack_config(void)
{
	int indexversion_value;
	int limit;
	unsigned long packsizelimit_value;

	if (!git_config_get_ulong("pack.depth", &max_depth)) {
		if (max_depth > MAX_DEPTH)
			max_depth = MAX_DEPTH;
	}
