 	switch (*arg) {
 	case '-':
 		if (skip_prefix(arg, "-width", &arg)) {
 			if (*arg == '=')
 				width = strtoul(arg + 1, &end, 10);
 			else if (!*arg && !av[1])
-				die("Option '--stat-width' requires a value");
+				die_want_option("--stat-width");
 			else if (!*arg) {
 				width = strtoul(av[1], &end, 10);
 				argcount = 2;
 			}
 		} else if (skip_prefix(arg, "-name-width", &arg)) {
 			if (*arg == '=')
 				name_width = strtoul(arg + 1, &end, 10);
 			else if (!*arg && !av[1])
-				die("Option '--stat-name-width' requires a value");
+				die_want_option("--stat-name-width");
 			else if (!*arg) {
 				name_width = strtoul(av[1], &end, 10);
 				argcount = 2;
 			}
 		} else if (skip_prefix(arg, "-graph-width", &arg)) {
 			if (*arg == '=')
 				graph_width = strtoul(arg + 1, &end, 10);
 			else if (!*arg && !av[1])
-				die("Option '--stat-graph-width' requires a value");
+				die_want_option("--stat-graph-width");
 			else if (!*arg) {
 				graph_width = strtoul(av[1], &end, 10);
 				argcount = 2;
 			}
 		} else if (skip_prefix(arg, "-count", &arg)) {
 			if (*arg == '=')
 				count = strtoul(arg + 1, &end, 10);
 			else if (!*arg && !av[1])
-				die("Option '--stat-count' requires a value");
+				die_want_option("--stat-count");
 			else if (!*arg) {
 				count = strtoul(av[1], &end, 10);
 				argcount = 2;
 			}
 		}
 		break;
