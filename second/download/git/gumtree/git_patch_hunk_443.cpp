 		if (abbrev < minimum_abbrev || abbrev > 40)
 			return -1;
 		default_abbrev = abbrev;
 		return 0;
 	}
 
+	if (!strcmp(var, "core.disambiguate"))
+		return set_disambiguate_hint_config(var, value);
+
 	if (!strcmp(var, "core.loosecompression")) {
 		int level = git_config_int(var, value);
 		if (level == -1)
 			level = Z_DEFAULT_COMPRESSION;
 		else if (level < 0 || level > Z_BEST_COMPRESSION)
 			die(_("bad zlib compression level %d"), level);
