
	s = argv[*argc] = strdup(s);
	if (sanitize_paths) {
		sanitize_path(s, NULL);
	}

	memset(&globbuf, 0, sizeof globbuf);
	if (!exclude_server_path(s))
		glob(s, 0, NULL, &globbuf);
	if (globbuf.gl_pathc == 0) {
		(*argc)++;
		globfree(&globbuf);
		return;
	}
	for (i = 0; i < maxargs - *argc && i < (int)globbuf.gl_pathc; i++) {
		if (i == 0)
			free(s);
		argv[*argc + i] = strdup(globbuf.gl_pathv[i]);
		if (!argv[*argc + i])
			out_of_memory("glob_expand");
	}
	globfree(&globbuf);
	*argc += i;
#endif
}

/* This routine is only used in daemon mode. */
void glob_expand(char *base1, char **argv, int *argc, int maxargs)
{
