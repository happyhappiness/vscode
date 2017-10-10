	}

	if (!strcmp(var, "pack.packsizelimit")) {
		pack_size_limit_cfg = git_config_ulong(var, value);
		return 0;
	}

	if (!strcmp(var, "pack.compression")) {
		int level = git_config_int(var, value);
		if (level == -1)
			level = Z_DEFAULT_COMPRESSION;
		else if (level < 0 || level > Z_BEST_COMPRESSION)
			die(_("bad pack compression level %d"), level);
		pack_compression_level = level;
		pack_compression_seen = 1;
		return 0;
	}

	/* Add other config variables here and to Documentation/config.txt. */
	return 0;
}

/*
 * All source specific fields in the union, die_on_error, name and the callbacks
