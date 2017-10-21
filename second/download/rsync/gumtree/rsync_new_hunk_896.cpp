		printf("%12.0f", (double)buf.st_size);
	printf(" %6ld.%-6ld %6ld %s %s%s\n",
	       (long)buf.st_uid, (long)buf.st_gid, (long)buf.st_nlink,
	       datebuf, fname, linkbuf);
}

static struct poptOption long_options[] = {
  /* longName, shortName, argInfo, argPtr, value, descrip, argDesc */
#ifdef SUPPORT_XATTRS
  {"fake-super",      'f', POPT_ARG_VAL,    &am_root, -1, 0, 0 },
#endif
  {"help",            'h', POPT_ARG_NONE,   0, 'h', 0, 0 },
  {0,0,0,0,0,0,0}
};

static void tls_usage(int ret)
{
  FILE *F = ret ? stderr : stdout;
  fprintf(F,"usage: " PROGRAM " [OPTIONS] FILE ...\n");
  fprintf(F,"Trivial file listing program for portably checking rsync\n");
  fprintf(F,"\nOptions:\n");
#ifdef SUPPORT_XATTRS
  fprintf(F," -f, --fake-super            display attributes including fake-super xattrs\n");
#endif
  fprintf(F," -h, --help                  show this help\n");
  exit(ret);
}

int
main(int argc, char *argv[])
{
	poptContext pc;
	const char **extra_args;
	int opt;

	pc = poptGetContext(PROGRAM, argc, (const char **)argv,
			    long_options, 0);
	while ((opt = poptGetNextOpt(pc)) != -1) {
		switch (opt) {
		case 'h':
			tls_usage(0);
		default:
			fprintf(stderr,
			        "%s: %s\n",
				poptBadOption(pc, POPT_BADOPTION_NOALIAS),
				poptStrerror(opt));
			tls_usage(1);
		}
	}

	extra_args = poptGetArgs(pc);
	if (!extra_args || *extra_args == NULL)
		tls_usage(1);

	for (; *extra_args; extra_args++)
		list_file(*extra_args);
	poptFreeContext(pc);

	return 0;
}
