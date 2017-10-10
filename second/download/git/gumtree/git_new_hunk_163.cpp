	int width = options->stat_width;
	int name_width = options->stat_name_width;
	int graph_width = options->stat_graph_width;
	int count = options->stat_count;
	int argcount = 1;

	if (!skip_prefix(arg, "--stat", &arg))
		die("BUG: stat option does not begin with --stat: %s", arg);
	end = (char *)arg;

	switch (*arg) {
	case '-':
		if (skip_prefix(arg, "-width", &arg)) {
			if (*arg == '=')
				width = strtoul(arg + 1, &end, 10);
			else if (!*arg && !av[1])
				die("Option '--stat-width' requires a value");
			else if (!*arg) {
				width = strtoul(av[1], &end, 10);
				argcount = 2;
			}
		} else if (skip_prefix(arg, "-name-width", &arg)) {
			if (*arg == '=')
				name_width = strtoul(arg + 1, &end, 10);
			else if (!*arg && !av[1])
				die("Option '--stat-name-width' requires a value");
			else if (!*arg) {
				name_width = strtoul(av[1], &end, 10);
				argcount = 2;
			}
		} else if (skip_prefix(arg, "-graph-width", &arg)) {
			if (*arg == '=')
				graph_width = strtoul(arg + 1, &end, 10);
			else if (!*arg && !av[1])
				die("Option '--stat-graph-width' requires a value");
			else if (!*arg) {
				graph_width = strtoul(av[1], &end, 10);
				argcount = 2;
			}
		} else if (skip_prefix(arg, "-count", &arg)) {
			if (*arg == '=')
				count = strtoul(arg + 1, &end, 10);
			else if (!*arg && !av[1])
				die("Option '--stat-count' requires a value");
			else if (!*arg) {
				count = strtoul(av[1], &end, 10);
