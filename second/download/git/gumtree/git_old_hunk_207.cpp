		int flags = 0, opt_flags = 0;

		if (!long_name)
			continue;

again:
		rest = skip_prefix(arg, long_name);
		if (options->type == OPTION_ARGUMENT) {
			if (!rest)
				continue;
			if (*rest == '=')
				return opterror(options, "takes no value", flags);
			if (*rest)
