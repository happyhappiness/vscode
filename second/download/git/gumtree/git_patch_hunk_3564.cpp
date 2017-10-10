 
 	/* We need at least one parameter -- tree-ish */
 	if (argc < 1)
 		usage_with_options(archive_usage, opts);
 	*ar = lookup_archiver(format);
 	if (!*ar || (is_remote && !((*ar)->flags & ARCHIVER_REMOTE)))
-		die("Unknown archive format '%s'", format);
+		die(_("Unknown archive format '%s'"), format);
 
 	args->compression_level = Z_DEFAULT_COMPRESSION;
 	if (compression_level != -1) {
 		if ((*ar)->flags & ARCHIVER_WANT_COMPRESSION_LEVELS)
 			args->compression_level = compression_level;
 		else {
-			die("Argument not supported for format '%s': -%d",
+			die(_("Argument not supported for format '%s': -%d"),
 					format, compression_level);
 		}
 	}
 	args->verbose = verbose;
 	args->base = base;
 	args->baselen = strlen(base);
