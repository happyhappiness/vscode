		else if (level < 0 || level > Z_BEST_COMPRESSION)
			die(_("bad zlib compression level %d"), level);
		core_compression_level = level;
		core_compression_seen = 1;
		if (!zlib_compression_seen)
			zlib_compression_level = level;
		if (!pack_compression_seen)
			pack_compression_level = level;
		return 0;
	}

	if (!strcmp(var, "core.packedgitwindowsize")) {
		int pgsz_x2 = getpagesize() * 2;
		packed_git_window_size = git_config_ulong(var, value);
