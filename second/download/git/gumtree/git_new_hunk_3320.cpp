		delta_base_cache_limit = git_config_ulong(var, value);
		return 0;
	}

	if (!strcmp(var, "core.autocrlf")) {
		if (value && !strcasecmp(value, "input")) {
			auto_crlf = AUTO_CRLF_INPUT;
			return 0;
		}
		auto_crlf = git_config_bool(var, value);
		return 0;
	}
