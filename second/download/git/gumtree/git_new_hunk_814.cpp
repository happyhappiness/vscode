					"ignore");
		else if (strcmp(value, "untracked") &&
			 strcmp(value, "dirty") &&
			 strcmp(value, "all") &&
			 strcmp(value, "none"))
			warning("Invalid parameter '%s' for config option "
					"'submodule.%s.ignore'", value, name.buf);
		else {
			free((void *) submodule->ignore);
			submodule->ignore = xstrdup(value);
		}
	} else if (!strcmp(item.buf, "url")) {
		if (!value) {
