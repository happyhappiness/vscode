		s += strlen(base);
	}

	s = strdup(s);
	if (!s) out_of_memory("glob_expand");

	base = (char *)malloc(strlen(base1)+3);
	if (!base) out_of_memory("glob_expand");

	sprintf(base," %s/", base1);

	q = s;
	while ((p = strstr(q,base)) && ((*argc) < maxargs)) {
		/* split it at this point */
		*p = 0;
		glob_expand_one(q, argv, argc, maxargs);
