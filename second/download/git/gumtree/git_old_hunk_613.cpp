	}

	if (!strcmp(var, "pack.packsizelimit")) {
		pack_size_limit_cfg = git_config_ulong(var, value);
		return 0;
	}
	/* Add other config variables here and to Documentation/config.txt. */
	return 0;
}

/*
 * All source specific fields in the union, die_on_error, name and the callbacks
