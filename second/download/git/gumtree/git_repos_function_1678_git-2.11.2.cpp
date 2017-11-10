static void git_pack_config(void)
{
	int indexversion_value;
	int limit;
	unsigned long packsizelimit_value;

	if (!git_config_get_ulong("pack.depth", &max_depth)) {
		if (max_depth > MAX_DEPTH)
			max_depth = MAX_DEPTH;
	}
	if (!git_config_get_int("pack.indexversion", &indexversion_value)) {
		pack_idx_opts.version = indexversion_value;
		if (pack_idx_opts.version > 2)
			git_die_config("pack.indexversion",
					"bad pack.indexversion=%"PRIu32, pack_idx_opts.version);
	}
	if (!git_config_get_ulong("pack.packsizelimit", &packsizelimit_value))
		max_packsize = packsizelimit_value;

	if (!git_config_get_int("fastimport.unpacklimit", &limit))
		unpack_limit = limit;
	else if (!git_config_get_int("transfer.unpacklimit", &limit))
		unpack_limit = limit;

	git_config(git_default_config, NULL);
}