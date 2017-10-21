	if (!s) out_of_memory("glob_expand");

	if (asprintf(&base," %s/", base1) <= 0) out_of_memory("glob_expand");
	base_len++;

	q = s;
	while ((p = strstr(q,base)) != NULL && *argc < maxargs) {
		/* split it at this point */
		*p = 0;
		glob_expand_one(q, argv, argc, maxargs);
		q = p + base_len;
	}

	if (*q && *argc < maxargs)
		glob_expand_one(q, argv, argc, maxargs);

	free(s);
	free(base);
}

/**
