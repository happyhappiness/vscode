int main(int argc, char **argv) {
	char **opts, **opt, *pfx;
	int i;

	if (argc <= 1) {
		print_usage(argv[0]);
        }

	opts = malloc((2 * argc + 1) * sizeof (* opts));	/* __MEM_CHECKED__ */
	if(!opts) {
		perror(argv[0]);
		exit(2);
	}

	if (argc < 2)
	{
	  fprintf (stderr,
		   "Command line usage: %s [flags] -- prefix [recipients]\n",
		   argv[0]);
	  return 1;
	}

	opt = opts;
	*opt++ = argv[1];
	pfx = NULL;

	for(i = 2; i < argc; ) {
		if(!strcmp(argv[i], "--")) {
			i += 2;
			if(i > argc) {
				print_usage(argv[0]);
			}
			pfx = argv[i-1];
		}
		if(pfx)
			*opt++ = pfx;
		*opt++ = argv[i++];
	}
	*opt = NULL;

	execvp(opts[0], opts);
	perror(argv[0]);
	return 2;
}