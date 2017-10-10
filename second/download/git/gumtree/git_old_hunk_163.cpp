	int width = options->stat_width;
	int name_width = options->stat_name_width;
	int graph_width = options->stat_graph_width;
	int count = options->stat_count;
	int argcount = 1;

	arg += strlen("--stat");
	end = (char *)arg;

	switch (*arg) {
	case '-':
		if (starts_with(arg, "-width")) {
			arg += strlen("-width");
			if (*arg == '=')
				width = strtoul(arg + 1, &end, 10);
			else if (!*arg && !av[1])
				die("Option '--stat-width' requires a value");
			else if (!*arg) {
				width = strtoul(av[1], &end, 10);
				argcount = 2;
			}
		} else if (starts_with(arg, "-name-width")) {
			arg += strlen("-name-width");
			if (*arg == '=')
				name_width = strtoul(arg + 1, &end, 10);
			else if (!*arg && !av[1])
				die("Option '--stat-name-width' requires a value");
			else if (!*arg) {
				name_width = strtoul(av[1], &end, 10);
				argcount = 2;
			}
		} else if (starts_with(arg, "-graph-width")) {
			arg += strlen("-graph-width");
			if (*arg == '=')
				graph_width = strtoul(arg + 1, &end, 10);
			else if (!*arg && !av[1])
				die("Option '--stat-graph-width' requires a value");
			else if (!*arg) {
				graph_width = strtoul(av[1], &end, 10);
				argcount = 2;
			}
		} else if (starts_with(arg, "-count")) {
			arg += strlen("-count");
			if (*arg == '=')
				count = strtoul(arg + 1, &end, 10);
			else if (!*arg && !av[1])
				die("Option '--stat-count' requires a value");
			else if (!*arg) {
				count = strtoul(av[1], &end, 10);
