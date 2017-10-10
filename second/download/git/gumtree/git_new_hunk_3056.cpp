	} else if (!strcmp(arg, "--children")) {
		revs->children.name = "children";
		revs->limited = 1;
	} else if (!strcmp(arg, "--ignore-missing")) {
		revs->ignore_missing = 1;
	} else {
		int opts = diff_opt_parse(&revs->diffopt, argv, argc, revs->prefix);
		if (!opts)
			unkv[(*unkc)++] = arg;
		return opts;
	}
	if (revs->graph && revs->track_linear)
		die("--show-linear-break and --graph are incompatible");
