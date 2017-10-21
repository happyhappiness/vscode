		out_of_memory("glob_expand_module");
	base_len++;

	for (s = arg; *s; s = p + base_len) {
		if ((p = strstr(s, base)) != NULL)
			*p = '\0'; /* split it at this point */
		glob_expand(s, argv_ptr, argc_ptr, maxargs_ptr);
		if (!p)
			break;
	}

	free(arg);
	free(base);
