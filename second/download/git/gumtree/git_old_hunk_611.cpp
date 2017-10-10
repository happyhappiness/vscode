	if (!strcmp(var, "core.warnambiguousrefs")) {
		warn_ambiguous_refs = git_config_bool(var, value);
		return 0;
	}

	if (!strcmp(var, "core.abbrev")) {
		int abbrev = git_config_int(var, value);
		if (abbrev < minimum_abbrev || abbrev > 40)
			return -1;
		default_abbrev = abbrev;
		return 0;
	}

	if (!strcmp(var, "core.disambiguate"))
		return set_disambiguate_hint_config(var, value);

