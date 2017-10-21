	lock.l_len = len;
	lock.l_pid = 0;
	
	return fcntl(fd,F_SETLK,&lock) == 0;
}

static int exclude_server_path(char *arg)
{
	char *s;
	extern struct exclude_struct **server_exclude_list;

	if (server_exclude_list) {
		for (s = arg; (s = strchr(s, '/')) != NULL; ) {
			*s = '\0';
			if (check_exclude(server_exclude_list, arg, 1)) {
				/* We must leave arg truncated! */
				return 1;
			}
			*s++ = '/';
		}
	}
	return 0;
}

static void glob_expand_one(char *s, char **argv, int *argc, int maxargs)
{
#if !(defined(HAVE_GLOB) && defined(HAVE_GLOB_H))
	if (!*s) s = ".";
	s = argv[*argc] = strdup(s);
	exclude_server_path(s);
	(*argc)++;
#else
	extern int sanitize_paths;
	glob_t globbuf;
	int i;

	if (!*s) s = ".";

	s = argv[*argc] = strdup(s);
	if (sanitize_paths) {
		sanitize_path(s, NULL);
	}

	memset(&globbuf, 0, sizeof(globbuf));
	if (!exclude_server_path(s))
		glob(s, 0, NULL, &globbuf);
	if (globbuf.gl_pathc == 0) {
		(*argc)++;
		globfree(&globbuf);
		return;
	}
	for (i=0; i<(maxargs - (*argc)) && i < (int) globbuf.gl_pathc;i++) {
		if (i == 0) free(s);
		argv[(*argc) + i] = strdup(globbuf.gl_pathv[i]);
		if (!argv[(*argc) + i]) out_of_memory("glob_expand");
	}
	globfree(&globbuf);
	(*argc) += i;
#endif
}

/* This routine is only used in daemon mode. */
void glob_expand(char *base1, char **argv, int *argc, int maxargs)
{
	char *s = argv[*argc];
	char *p, *q;
	char *base = base1;
	int base_len = strlen(base);

	if (!s || !*s) return;

	if (strncmp(s, base, base_len) == 0)
		s += base_len;

	s = strdup(s);
	if (!s) out_of_memory("glob_expand");

	if (asprintf(&base," %s/", base1) <= 0) out_of_memory("glob_expand");
	base_len++;

	q = s;
	while ((p = strstr(q,base)) && ((*argc) < maxargs)) {
		/* split it at this point */
		*p = 0;
		glob_expand_one(q, argv, argc, maxargs);
		q = p + base_len;
	}

	if (*q && (*argc < maxargs)) glob_expand_one(q, argv, argc, maxargs);

	free(s);
	free(base);
