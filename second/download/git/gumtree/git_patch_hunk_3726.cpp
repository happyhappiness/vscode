 	else if ((argcount = parse_long_opt("output", av, &optarg))) {
 		const char *path = prefix_filename(prefix, strlen(prefix), optarg);
 		options->file = fopen(path, "w");
 		if (!options->file)
 			die_errno("Could not open '%s'", path);
 		options->close_file = 1;
+		if (options->use_color != GIT_COLOR_ALWAYS)
+			options->use_color = GIT_COLOR_NEVER;
 		return argcount;
 	} else
 		return 0;
 	return 1;
 }
 
