 		int offending = parse_diff_filter_opt(optarg, options);
 		if (offending)
 			die("unknown change class '%c' in --diff-filter=%s",
 			    offending, optarg);
 		return argcount;
 	}
+	else if (!strcmp(arg, "--no-abbrev"))
+		options->abbrev = 0;
 	else if (!strcmp(arg, "--abbrev"))
 		options->abbrev = DEFAULT_ABBREV;
 	else if (skip_prefix(arg, "--abbrev=", &arg)) {
 		options->abbrev = strtoul(arg, NULL, 10);
 		if (options->abbrev < MINIMUM_ABBREV)
 			options->abbrev = MINIMUM_ABBREV;
