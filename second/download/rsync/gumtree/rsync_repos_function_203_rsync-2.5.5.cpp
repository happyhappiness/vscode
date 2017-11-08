static void glob_expand_one(char *s, char **argv, int *argc, int maxargs)
{
#if !(defined(HAVE_GLOB) && defined(HAVE_GLOB_H))
	if (!*s) s = ".";
	argv[*argc] = strdup(s);
	(*argc)++;
	return;
#else
	extern int sanitize_paths;
	glob_t globbuf;
	int i;

	if (!*s) s = ".";

	argv[*argc] = strdup(s);
	if (sanitize_paths) {
		sanitize_path(argv[*argc], NULL);
	}

	memset(&globbuf, 0, sizeof(globbuf));
	glob(argv[*argc], 0, NULL, &globbuf);
	if (globbuf.gl_pathc == 0) {
		(*argc)++;
		globfree(&globbuf);
		return;
	}
	for (i=0; i<(maxargs - (*argc)) && i < (int) globbuf.gl_pathc;i++) {
		if (i == 0) free(argv[*argc]);
		argv[(*argc) + i] = strdup(globbuf.gl_pathv[i]);
		if (!argv[(*argc) + i]) out_of_memory("glob_expand");
	}
	globfree(&globbuf);
	(*argc) += i;
#endif
}