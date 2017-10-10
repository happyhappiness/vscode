 	} else if (!strcmp(arg, "-n")) {
 		if (argc <= 1)
 			return error("-n requires an argument");
 		revs->max_count = atoi(argv[1]);
 		revs->no_walk = 0;
 		return 2;
-	} else if (starts_with(arg, "-n")) {
-		revs->max_count = atoi(arg + 2);
+	} else if (skip_prefix(arg, "-n", &optarg)) {
+		revs->max_count = atoi(optarg);
 		revs->no_walk = 0;
 	} else if ((argcount = parse_long_opt("max-age", argv, &optarg))) {
 		revs->max_age = atoi(optarg);
 		return argcount;
 	} else if ((argcount = parse_long_opt("since", argv, &optarg))) {
 		revs->max_age = approxidate(optarg);
