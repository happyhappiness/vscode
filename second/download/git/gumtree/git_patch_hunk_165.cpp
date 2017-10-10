 			die("unknown change class '%c' in --diff-filter=%s",
 			    offending, optarg);
 		return argcount;
 	}
 	else if (!strcmp(arg, "--abbrev"))
 		options->abbrev = DEFAULT_ABBREV;
-	else if (starts_with(arg, "--abbrev=")) {
-		options->abbrev = strtoul(arg + 9, NULL, 10);
+	else if (skip_prefix(arg, "--abbrev=", &arg)) {
+		options->abbrev = strtoul(arg, NULL, 10);
 		if (options->abbrev < MINIMUM_ABBREV)
 			options->abbrev = MINIMUM_ABBREV;
 		else if (40 < options->abbrev)
 			options->abbrev = 40;
 	}
 	else if ((argcount = parse_long_opt("src-prefix", av, &optarg))) {
