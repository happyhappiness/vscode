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
