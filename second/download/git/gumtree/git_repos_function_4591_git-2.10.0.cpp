int cmd_annotate(int argc, const char **argv, const char *prefix)
{
	struct argv_array args = ARGV_ARRAY_INIT;
	int i;

	argv_array_pushl(&args, "annotate", "-c", NULL);

	for (i = 1; i < argc; i++) {
		argv_array_push(&args, argv[i]);
	}

	return cmd_blame(args.argc, args.argv, prefix);
}