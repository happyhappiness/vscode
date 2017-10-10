 		return 0;
 	}
 	if (!strcmp(k, "pack.depth")) {
 		depth = git_config_int(k, v);
 		return 0;
 	}
-	if (!strcmp(k, "pack.compression")) {
-		int level = git_config_int(k, v);
-		if (level == -1)
-			level = Z_DEFAULT_COMPRESSION;
-		else if (level < 0 || level > Z_BEST_COMPRESSION)
-			die("bad pack compression level %d", level);
-		pack_compression_level = level;
-		pack_compression_seen = 1;
-		return 0;
-	}
 	if (!strcmp(k, "pack.deltacachesize")) {
 		max_delta_cache_size = git_config_int(k, v);
 		return 0;
 	}
 	if (!strcmp(k, "pack.deltacachelimit")) {
 		cache_max_small_delta_size = git_config_int(k, v);
